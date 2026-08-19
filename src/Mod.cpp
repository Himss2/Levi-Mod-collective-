#include "levivisuals/Mod.hpp"

#include "levivisuals/Ids.hpp"

#include <cerrno>
#include <cstdlib>
#include <filesystem>
#include <optional>
#include <string>

namespace levivisuals {

namespace {

std::optional<bool> parseBool(
    std::string_view value
) {
    if (
        value == "true" ||
        value == "1" ||
        value == "on" ||
        value == "enabled"
    ) {
        return true;
    }

    if (
        value == "false" ||
        value == "0" ||
        value == "off" ||
        value == "disabled"
    ) {
        return false;
    }

    return std::nullopt;
}

std::optional<float> parseFloat(
    std::string_view value
) {
    std::string text(value);

    char* end = nullptr;

    errno = 0;

    const float parsed =
        std::strtof(
            text.c_str(),
            &end
        );

    if (
        end == text.c_str() ||
        end == nullptr ||
        *end != '\0' ||
        errno == ERANGE
    ) {
        return std::nullopt;
    }

    return parsed;
}

} // namespace

LeviVisualsMod&
LeviVisualsMod::instance() {
    static LeviVisualsMod mod;

    return mod;
}

LeviVisualsMod::LeviVisualsMod()
    : self_(
        *ll::mod::NativeMod::current()
    ) {
}

bool LeviVisualsMod::load() {
    std::lock_guard lock(
        configMutex_
    );

    std::error_code error;

    std::filesystem::create_directories(
        self_.getConfigDir(),
        error
    );

    if (error) {
        self_.getLogger().error(
            "Failed to create config directory: {}",
            error.message()
        );

        return false;
    }

    configFile_.emplace(
        AppConfig{},
        self_.getConfigDir() /
            "config.json",
        self_.getConfigDir() /
            "config.schema.json"
    );

    if (!configFile_->load()) {
        self_.getLogger().error(
            "Failed to load configuration"
        );

        configFile_.reset();

        return false;
    }

    normalizeConfig(
        configFile_->value()
    );

    if (!configFile_->save()) {
        self_.getLogger().error(
            "Failed to save normalized configuration"
        );

        configFile_.reset();

        return false;
    }

    applyConfigLocked();

    self_.getLogger().info(
        "Loaded {} {} for Minecraft 1.26.44.3",
        self_.getName(),
        self_.getVersion()
    );

    return true;
}

bool LeviVisualsMod::enable() {
    AppConfig snapshot;

    {
        std::lock_guard lock(
            configMutex_
        );

        if (!configFile_) {
            self_.getLogger().error(
                "Cannot enable before configuration is loaded"
            );

            return false;
        }

        applyConfigLocked();

        snapshot =
            configFile_->value();
    }

    runtimeEnabled_.store(
        true,
        std::memory_order_release
    );

    if (
        !modMenu_.registerAll(
            *this,
            snapshot
        )
    ) {
        runtimeEnabled_.store(
            false,
            std::memory_order_release
        );

        self_.getLogger().error(
            "Failed to register Levi Mod Menu entries"
        );

        return false;
    }

    self_.getLogger().info(
        "Levi Visuals foundation enabled"
    );

    return true;
}

bool LeviVisualsMod::disable() {
    runtimeEnabled_.store(
        false,
        std::memory_order_release
    );

    freelook_.resetInteraction();

    modMenu_.unregisterAll();

    self_.getLogger().info(
        "Levi Visuals disabled"
    );

    return true;
}

bool LeviVisualsMod::unload() {
    disable();

    std::lock_guard lock(
        configMutex_
    );

    configFile_.reset();

    self_.getLogger().info(
        "Levi Visuals unloaded"
    );

    return true;
}

void LeviVisualsMod::handleModuleToggle(
    std::string_view moduleId,
    bool enabled
) {
    std::lock_guard lock(
        configMutex_
    );

    if (!configFile_) {
        return;
    }

    auto& config =
        configFile_->value();

    if (
        moduleId ==
        ids::ViewModelModule
    ) {
        config.viewModelEnabled =
            enabled;

        viewModel_.setEnabled(
            enabled
        );
    } else if (
        moduleId ==
        ids::FreelookModule
    ) {
        config.freelookEnabled =
            enabled;

        freelook_.setEnabled(
            enabled
        );

        if (!enabled) {
            freelook_
                .resetInteraction();
        }
    } else if (
        moduleId ==
        ids::ItemPhysicsModule
    ) {
        config.itemPhysicsEnabled =
            enabled;

        itemPhysics_.setEnabled(
            enabled
        );
    } else {
        return;
    }

    saveConfigLocked(
        "module toggle"
    );
}

void LeviVisualsMod::handleConfigChanged(
    std::string_view moduleId,
    std::string_view key,
    std::string_view value
) {
    std::lock_guard lock(
        configMutex_
    );

    if (!configFile_) {
        return;
    }

    auto& config =
        configFile_->value();

    bool changed = false;

    if (
        moduleId ==
            ids::ViewModelModule &&
        key ==
            ids::ViewModelItemFov
    ) {
        if (
            const auto parsed =
                parseFloat(value)
        ) {
            config.viewModelItemFov =
                *parsed;

            normalizeConfig(config);

            viewModel_.setItemFov(
                config.viewModelItemFov
            );

            changed = true;
        }
    } else if (
        moduleId ==
            ids::FreelookModule &&
        key ==
            ids::FreelookSensitivity
    ) {
        if (
            const auto parsed =
                parseFloat(value)
        ) {
            config.freelookSensitivity =
                *parsed;

            normalizeConfig(config);

            freelook_.setSensitivity(
                config.freelookSensitivity
            );

            changed = true;
        }
    } else if (
        moduleId ==
            ids::ItemPhysicsModule &&
        key ==
            ids::ItemPhysicsSpeed
    ) {
        if (
            const auto parsed =
                parseFloat(value)
        ) {
            config.itemPhysicsSpeed =
                *parsed;

            normalizeConfig(config);

            itemPhysics_.setSpeed(
                config.itemPhysicsSpeed
            );

            changed = true;
        }
    } else if (
        moduleId ==
            ids::ItemPhysicsModule &&
        key ==
            ids::ItemPhysicsSmooth
    ) {
        if (
            const auto parsed =
                parseBool(value)
        ) {
            config.itemPhysicsSmooth =
                *parsed;

            itemPhysics_
                .setSmoothRotations(
                    *parsed
                );

            changed = true;
        }
    } else if (
        moduleId ==
            ids::ItemPhysicsModule &&
        key ==
            ids::ItemPhysicsPreserve
    ) {
        if (
            const auto parsed =
                parseBool(value)
        ) {
            config
                .itemPhysicsPreserveRotations =
                    *parsed;

            itemPhysics_
                .setPreserveRotations(
                    *parsed
                );

            changed = true;
        }
    }

    if (changed) {
        saveConfigLocked(key);
    }
}

void LeviVisualsMod::handleButtonEvent(
    std::string_view buttonId,
    pl::modmenu::ButtonEvent event,
    float value
) {
    (void)value;

    if (
        buttonId !=
            ids::FreelookButton ||
        !runtimeEnabled()
    ) {
        return;
    }

    if (
        event ==
        pl::modmenu::ButtonEvent::Down
    ) {
        freelook_.setButtonDown(
            true
        );
    } else if (
        event ==
        pl::modmenu::ButtonEvent::Up
    ) {
        freelook_.setButtonDown(
            false
        );
    }
}

void LeviVisualsMod::applyConfigLocked() {
    if (!configFile_) {
        return;
    }

    auto& config =
        configFile_->value();

    normalizeConfig(config);

    viewModel_.setEnabled(
        config.viewModelEnabled
    );

    viewModel_.setItemFov(
        config.viewModelItemFov
    );

    freelook_.setEnabled(
        config.freelookEnabled
    );

    freelook_.setSensitivity(
        config.freelookSensitivity
    );

    itemPhysics_.setEnabled(
        config.itemPhysicsEnabled
    );

    itemPhysics_.setSpeed(
        config.itemPhysicsSpeed
    );

    itemPhysics_.setSmoothRotations(
        config.itemPhysicsSmooth
    );

    itemPhysics_.setPreserveRotations(
        config
            .itemPhysicsPreserveRotations
    );
}

bool LeviVisualsMod::saveConfigLocked(
    std::string_view reason
) {
    if (!configFile_) {
        return false;
    }

    normalizeConfig(
        configFile_->value()
    );

    if (!configFile_->save()) {
        self_.getLogger().warn(
            "Failed to save configuration after {}",
            reason
        );

        return false;
    }

    return true;
}

} // namespace levivisuals
