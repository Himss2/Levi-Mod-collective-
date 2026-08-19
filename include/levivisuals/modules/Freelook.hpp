#pragma once

#include "levivisuals/modules/FeatureModule.hpp"

#include <atomic>

namespace levivisuals::modules {

class Freelook final : public FeatureModule {
public:
    void setSensitivity(float value) noexcept;

    [[nodiscard]]
    float sensitivity() const noexcept;

    void setButtonDown(bool down) noexcept;

    void resetInteraction() noexcept;

    [[nodiscard]]
    bool active() const noexcept;

private:
    std::atomic<float> sensitivity_{1.0F};
    std::atomic_bool buttonDown_{false};
};

} // namespace levivisuals::modules
