#include "levivisuals/modules/Freelook.hpp"

#include <algorithm>

namespace levivisuals::modules {

void Freelook::setSensitivity(
    float value
) noexcept {
    sensitivity_.store(
        std::clamp(
            value,
            0.1F,
            3.0F
        ),
        std::memory_order_release
    );
}

float Freelook::sensitivity()
    const noexcept {
    return sensitivity_.load(
        std::memory_order_acquire
    );
}

void Freelook::setButtonDown(
    bool down
) noexcept {
    buttonDown_.store(
        down,
        std::memory_order_release
    );
}

void Freelook::resetInteraction()
    noexcept {
    buttonDown_.store(
        false,
        std::memory_order_release
    );
}

bool Freelook::active()
    const noexcept {
    return
        enabled() &&
        buttonDown_.load(
            std::memory_order_acquire
        );
}

} // namespace levivisuals::modules
