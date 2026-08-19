#include "levivisuals/Config.hpp"

#include <algorithm>

namespace levivisuals {

void normalizeConfig(
    AppConfig& config
) noexcept {
    config.version = 1;

    config.viewModelItemFov =
        std::clamp(
            config.viewModelItemFov,
            30.0F,
            120.0F
        );

    config.freelookSensitivity =
        std::clamp(
            config.freelookSensitivity,
            0.1F,
            3.0F
        );

    config.itemPhysicsSpeed =
        std::clamp(
            config.itemPhysicsSpeed,
            0.0F,
            3.0F
        );
}

} // namespace levivisuals
