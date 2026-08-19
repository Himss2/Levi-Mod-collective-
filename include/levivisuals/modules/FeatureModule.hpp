#pragma once

#include <atomic>

namespace levivisuals::modules {

class FeatureModule {
public:
    FeatureModule() = default;
    virtual ~FeatureModule() = default;

    FeatureModule(const FeatureModule&) = delete;
    FeatureModule& operator=(const FeatureModule&) = delete;

    void setEnabled(bool enabled) noexcept {
        enabled_.store(
            enabled,
            std::memory_order_release
        );
    }

    [[nodiscard]]
    bool enabled() const noexcept {
        return enabled_.load(
            std::memory_order_acquire
        );
    }

private:
    std::atomic_bool enabled_{false};
};

} // namespace levivisuals::modules
