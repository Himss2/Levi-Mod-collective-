#pragma once

#include "levivisuals/modules/FeatureModule.hpp"

#include <atomic>

namespace levivisuals::modules {

class ItemPhysics final : public FeatureModule {
public:
    void setSpeed(float value) noexcept;

    [[nodiscard]]
    float speed() const noexcept;

    void setSmoothRotations(bool value) noexcept;

    [[nodiscard]]
    bool smoothRotations() const noexcept;

    void setPreserveRotations(bool value) noexcept;

    [[nodiscard]]
    bool preserveRotations() const noexcept;

private:
    std::atomic<float> speed_{1.0F};
    std::atomic_bool smoothRotations_{true};
    std::atomic_bool preserveRotations_{true};
};

} // namespace levivisuals::modules
