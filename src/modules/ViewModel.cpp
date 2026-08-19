#include "levivisuals/modules/ViewModel.hpp"

#include <algorithm>

namespace levivisuals::modules {

void ViewModel::setItemFov(
    float value
) noexcept {
    itemFov_.store(
        std::clamp(
            value,
            30.0F,
            120.0F
        ),
        std::memory_order_release
    );
}

float ViewModel::itemFov() const noexcept {
    return itemFov_.load(
        std::memory_order_acquire
    );
}

} // namespace levivisuals::modules
