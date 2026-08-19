#pragma once

#include "levivisuals/Config.hpp"

namespace levivisuals {
class LeviVisualsMod;
}

namespace levivisuals::ui {

class ModMenu final {
public:
    bool registerAll(
        LeviVisualsMod& mod,
        const AppConfig& config
    );

    void unregisterAll() noexcept;

    [[nodiscard]]
    bool registered() const noexcept {
        return registered_;
    }

private:
    bool registered_{false};
};

} // namespace levivisuals::ui
