#pragma once

#include "levivisuals/modules/FeatureModule.hpp"

#include <atomic>

namespace levivisuals::modules {

class ViewModel final : public FeatureModule {
public:
    void setItemFov(float value) noexcept;

    [[nodiscard]]
    float itemFov() const noexcept;

private:
    std::atomic<float> itemFov_{70.0F};
};

} // namespace levivisuals::modules
