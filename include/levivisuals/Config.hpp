#pragma once

#include <optional>
#include <string_view>

#include <pl/Config.hpp>

namespace levivisuals {

struct AppConfig {
    int version{1};

    bool viewModelEnabled{true};
    float viewModelItemFov{70.0F};

    bool freelookEnabled{true};
    float freelookSensitivity{1.0F};

    bool itemPhysicsEnabled{true};
    float itemPhysicsSpeed{1.0F};
    bool itemPhysicsSmooth{true};
    bool itemPhysicsPreserveRotations{true};
};

void normalizeConfig(AppConfig& config) noexcept;

} // namespace levivisuals

namespace pl::config {

template <>
struct Schema<levivisuals::AppConfig> {
    static constexpr std::string_view title =
        "Levi Visuals";

    static constexpr std::string_view description =
        "Configuration for ViewModel, Freelook and Item Physics.";

    static constexpr FieldSchema field(
        std::string_view name
    ) {
        if (name == "version") {
            return {
                "Version",
                "Configuration schema version managed by the mod.",
                std::nullopt,
                std::nullopt,
                true
            };
        }

        if (name == "viewModelEnabled") {
            return {
                "ViewModel Enabled",
                "Enable ViewModel.",
                std::nullopt,
                std::nullopt,
                false
            };
        }

        if (name == "viewModelItemFov") {
            return {
                "Item FOV",
                "First-person item field of view.",
                30.0,
                120.0,
                false
            };
        }

        if (name == "freelookEnabled") {
            return {
                "Freelook Enabled",
                "Enable Freelook.",
                std::nullopt,
                std::nullopt,
                false
            };
        }

        if (name == "freelookSensitivity") {
            return {
                "Sensitivity",
                "Freelook camera sensitivity.",
                0.1,
                3.0,
                false
            };
        }

        if (name == "itemPhysicsEnabled") {
            return {
                "Item Physics Enabled",
                "Enable Item Physics.",
                std::nullopt,
                std::nullopt,
                false
            };
        }

        if (name == "itemPhysicsSpeed") {
            return {
                "Speed",
                "Dropped-item rotation speed.",
                0.0,
                3.0,
                false
            };
        }

        if (name == "itemPhysicsSmooth") {
            return {
                "Smooth Rotations",
                "Smooth dropped-item rotations.",
                std::nullopt,
                std::nullopt,
                false
            };
        }

        if (name == "itemPhysicsPreserveRotations") {
            return {
                "Preserve Rotations",
                "Preserve per-entity orientation.",
                std::nullopt,
                std::nullopt,
                false
            };
        }

        return {};
    }
};

} // namespace pl::config
