#pragma once

#include "levivisuals/Config.hpp"
#include "levivisuals/modules/Freelook.hpp"
#include "levivisuals/modules/ItemPhysics.hpp"
#include "levivisuals/modules/ViewModel.hpp"
#include "levivisuals/ui/ModMenu.hpp"

#include <atomic>
#include <mutex>
#include <optional>
#include <string_view>

#include <pl/Mod.hpp>
#include <pl/ModMenu.hpp>

namespace levivisuals {

class LeviVisualsMod final {
public:
    static LeviVisualsMod& instance();

    LeviVisualsMod();

    LeviVisualsMod(const LeviVisualsMod&) = delete;
    LeviVisualsMod& operator=(
        const LeviVisualsMod&
    ) = delete;

    [[nodiscard]]
    ll::mod::NativeMod& getSelf() const noexcept {
        return self_;
    }

    bool load();
    bool enable();
    bool disable();
    bool unload();

    void handleModuleToggle(
        std::string_view moduleId,
        bool enabled
    );

    void handleConfigChanged(
        std::string_view moduleId,
        std::string_view key,
        std::string_view value
    );

    void handleButtonEvent(
        std::string_view buttonId,
        pl::modmenu::ButtonEvent event,
        float value
    );

    [[nodiscard]]
    bool runtimeEnabled() const noexcept {
        return runtimeEnabled_.load(
            std::memory_order_acquire
        );
    }

    [[nodiscard]]
    modules::ViewModel& viewModel() noexcept {
        return viewModel_;
    }

    [[nodiscard]]
    modules::Freelook& freelook() noexcept {
        return freelook_;
    }

    [[nodiscard]]
    modules::ItemPhysics& itemPhysics() noexcept {
        return itemPhysics_;
    }

private:
    void applyConfigLocked();

    bool saveConfigLocked(
        std::string_view reason
    );

private:
    ll::mod::NativeMod& self_;

    std::mutex configMutex_;

    std::optional<
        pl::config::ConfigFile<AppConfig>
    > configFile_;

    std::atomic_bool runtimeEnabled_{false};

    modules::ViewModel viewModel_;
    modules::Freelook freelook_;
    modules::ItemPhysics itemPhysics_;

    ui::ModMenu modMenu_;
};

} // namespace levivisuals
