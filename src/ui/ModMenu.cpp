#include "levivisuals/ui/ModMenu.hpp"

#include "levivisuals/Ids.hpp"
#include "levivisuals/Mod.hpp"

#include <string>
#include <string_view>

#include <pl/ModMenu.hpp>

namespace levivisuals::ui {

namespace {

std::string boolValue(
    bool value
) {
    return value
        ? "true"
        : "false";
}

void onToggle(
    std::string_view moduleId,
    bool enabled
) {
    LeviVisualsMod::instance()
        .handleModuleToggle(
            moduleId,
            enabled
        );
}

void onConfigChanged(
    std::string_view moduleId,
    std::string_view key,
    std::string_view value
) {
    LeviVisualsMod::instance()
        .handleConfigChanged(
            moduleId,
            key,
            value
        );
}

void onButtonEvent(
    std::string_view buttonId,
    pl::modmenu::ButtonEvent event,
    float value
) {
    LeviVisualsMod::instance()
        .handleButtonEvent(
            buttonId,
            event,
            value
        );
}

} // namespace

bool ModMenu::registerAll(
    LeviVisualsMod& mod,
    const AppConfig& config
) {
    unregisterAll();

    const auto modId =
        mod.getSelf().getId();

    const bool viewModelRegistered =
        pl::modmenu::ModuleBuilder(
            ids::ViewModelModule,
            "ViewModel"
        )
            .modId(modId)
            .description(
                "Customize first-person item position, rotation and scale."
            )
            .defaultEnabled(
                config.viewModelEnabled
            )
            .onToggle(onToggle)
            .config(
                ids::ViewModelItemFov,
                "Item FOV",
                pl::modmenu::ConfigType::
                    SliderFloat,
                std::to_string(
                    config.viewModelItemFov
                ),
                "30.0",
                "120.0"
            )
            .onConfigChanged(
                onConfigChanged
            )
            .registerModule();

    const bool freelookRegistered =
        pl::modmenu::ModuleBuilder(
            ids::FreelookModule,
            "Freelook"
        )
            .modId(modId)
            .description(
                "Move the camera without rotating the player body."
            )
            .defaultEnabled(
                config.freelookEnabled
            )
            .onToggle(onToggle)
            .config(
                ids::FreelookSensitivity,
                "Sensitivity",
                pl::modmenu::ConfigType::
                    SliderFloat,
                std::to_string(
                    config
                        .freelookSensitivity
                ),
                "0.1",
                "3.0"
            )
            .onConfigChanged(
                onConfigChanged
            )
            .registerModule();

    const bool itemPhysicsRegistered =
        pl::modmenu::ModuleBuilder(
            ids::ItemPhysicsModule,
            "Item Physics"
        )
            .modId(modId)
            .description(
                "Improved dropped-item orientation and motion."
            )
            .defaultEnabled(
                config.itemPhysicsEnabled
            )
            .onToggle(onToggle)
            .config(
                ids::ItemPhysicsSpeed,
                "Speed",
                pl::modmenu::ConfigType::
                    SliderFloat,
                std::to_string(
                    config.itemPhysicsSpeed
                ),
                "0.0",
                "3.0"
            )
            .config(
                ids::ItemPhysicsSmooth,
                "Smooth Rotations",
                pl::modmenu::ConfigType::
                    Toggle,
                boolValue(
                    config.itemPhysicsSmooth
                )
            )
            .config(
                ids::ItemPhysicsPreserve,
                "Preserve Rotations",
                pl::modmenu::ConfigType::
                    Toggle,
                boolValue(
                    config
                        .itemPhysicsPreserveRotations
                )
            )
            .onConfigChanged(
                onConfigChanged
            )
            .registerModule();

    if (
        !viewModelRegistered ||
        !freelookRegistered ||
        !itemPhysicsRegistered
    ) {
        unregisterAll();

        return false;
    }

    const bool buttonRegistered =
        pl::modmenu::ButtonBuilder(
            ids::FreelookButton,
            "Freelook Button"
        )
            .modId(modId)
            .moduleId(
                ids::FreelookModule
            )
            .label("Free")
            .behavior(
                pl::modmenu::
                    ButtonBehavior::Hold
            )
            .defaultVisible(true)
            .stylePreset(
                pl::modmenu::
                    ButtonStylePreset::Accent
            )
            .onEvent(onButtonEvent)
            .registerButton();

    if (!buttonRegistered) {
        unregisterAll();

        return false;
    }

    registered_ = true;

    return true;
}

void ModMenu::unregisterAll()
    noexcept {
    pl::modmenu::unregisterButton(
        ids::FreelookButton
    );

    pl::modmenu::unregisterModule(
        ids::ItemPhysicsModule
    );

    pl::modmenu::unregisterModule(
        ids::FreelookModule
    );

    pl::modmenu::unregisterModule(
        ids::ViewModelModule
    );

    registered_ = false;
}

} // namespace levivisuals::ui
