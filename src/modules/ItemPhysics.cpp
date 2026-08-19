#include "levivisuals/modules/ItemPhysics.hpp"

#include <algorithm>

namespace levivisuals::modules {

void ItemPhysics::setSpeed(
    float value
) noexcept {
    speed_.store(
        std::clamp(
            value,
            0.0F,
            3.0F
        ),
        std::memory_order_release
    );
}

float ItemPhysics::speed()
    const noexcept {
    return speed_.load(
        std::memory_order_acquire
    );
}

void ItemPhysics::setSmoothRotations(
    bool value
) noexcept {
    smoothRotations_.store(
        value,
        std::memory_order_release
    );
}

bool ItemPhysics::smoothRotations()
    const noexcept {
    return smoothRotations_.load(
        std::memory_order_acquire
    );
}

void ItemPhysics::setPreserveRotations(
    bool value
) noexcept {
    preserveRotations_.store(
        value,
        std::memory_order_release
    );
}

bool ItemPhysics::preserveRotations()
    const noexcept {
    return preserveRotations_.load(
        std::memory_order_acquire
    );
}

} // namespace levivisuals::modules
