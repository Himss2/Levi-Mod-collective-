cmake_minimum_required(VERSION 3.22)

project(
    LeviVisuals
    VERSION 0.1.1
    LANGUAGES CXX
)

if(NOT ANDROID)
    message(
        FATAL_ERROR
        "LeviVisuals must be built with the Android NDK toolchain."
    )
endif()

if(NOT CMAKE_ANDROID_ARCH_ABI STREQUAL "arm64-v8a")
    message(
        FATAL_ERROR
        "LeviVisuals currently supports arm64-v8a only."
    )
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# Commit preloader yang digunakan oleh LeviLauncher Android v1.5.15.
# Pin commit ini untuk menjaga kesesuaian ABI ModMenu.
FetchContent_Declare(
    preloader_android

    GIT_REPOSITORY
        https://github.com/LiteLDev/preloader-android.git

    GIT_TAG
        a2a7f29a8b690fd83fd8f331ea925d322ab1754c

    GIT_PROGRESS
        TRUE
)

FetchContent_MakeAvailable(preloader_android)

# Android logging library.
# Dibutuhkan oleh pl::Logger dan __android_log_print.
find_library(
    ANDROID_LOG_LIBRARY
    log
    REQUIRED
)

# Definisi target harus dibuat sebelum target_include_directories,
# target_compile_options, target_link_options dan target_link_libraries.
add_library(
    levi_visuals
    SHARED

    src/Entry.cpp
    src/Mod.cpp

    src/core/Config.cpp

    src/modules/ViewModel.cpp
    src/modules/Freelook.cpp
    src/modules/ItemPhysics.cpp

    src/ui/ModMenu.cpp
)

set_target_properties(
    levi_visuals

    PROPERTIES
        OUTPUT_NAME "levi_visuals"
)

target_include_directories(
    levi_visuals

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(
    levi_visuals

    PRIVATE
        -Wall
        -Wextra
        -Wpedantic

        -fvisibility=hidden
        -fvisibility-inlines-hidden

        -ffunction-sections
        -fdata-sections
)

# Kompatibilitas Android 16 KiB page size.
target_link_options(
    levi_visuals

    PRIVATE
        -Wl,--gc-sections
        -Wl,-z,max-page-size=16384
)

target_link_libraries(
    levi_visuals

    PRIVATE
        preloader

        nlohmann_json::nlohmann_json
        Boost::pfr
        magic_enum::magic_enum
        fmt::fmt

        ${ANDROID_LOG_LIBRARY}
)
