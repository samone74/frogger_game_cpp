cmake_minimum_required(VERSION 3.10)

project(game)

set(CMAKE_CXX_STANDARD 23)

# -----------------------------
# 1. Add your shared game engine
# -----------------------------
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../src
    ${CMAKE_BINARY_DIR}/src_build
)
# -----------------------------
# 2. SDL include directories
# -----------------------------
# Go from: android/app/src/main/cpp/
# Up to:   project-root/
set(ROOT_DIR ${CMAKE_SOURCE_DIR}/../../../)

set(SDL3_INCLUDE_DIR        ${ROOT_DIR}/../../lib/android/SDL3/prefab/modules/SDL3-Headers/include)
set(SDL3_IMAGE_INCLUDE_DIR  ${ROOT_DIR}/../../lib/android/SDL3_image/prefab/modules/SDL3_image-shared/include)
set(SDL3_TTF_INCLUDE_DIR    ${ROOT_DIR}/../../lib/android/SDL3_ttf/prefab/modules/SDL3_ttf-shared/include)

set(SDL3_LIB
    ${ROOT_DIR}/../../lib/android/SDL3/prefab/modules/SDL3-shared/libs/android.${ANDROID_ABI}/libSDL3.so)

set(SDL3_IMAGE_LIB
    ${ROOT_DIR}/../../lib/android/SDL3_image/prefab/modules/SDL3_image-shared/libs/android.${ANDROID_ABI}/libSDL3_image.so)

set(SDL3_TTF_LIB
    ${ROOT_DIR}/../../lib/android/SDL3_ttf/prefab/modules/SDL3_ttf-shared/libs/android.${ANDROID_ABI}/libSDL3_ttf.so)

# -----------------------------
# 4. Build your Android library
# -----------------------------
add_library(game SHARED
        android.cpp
)

# -----------------------------
# 5. Include directories
# -----------------------------
target_include_directories(game PRIVATE
        ${SDL3_INCLUDE_DIR}
        ${SDL3_IMAGE_INCLUDE_DIR}
        ${SDL3_TTF_INCLUDE_DIR}
)

# Also give SDL includes to your engine
target_include_directories(frogger_core PUBLIC
        ${SDL3_INCLUDE_DIR}
        ${SDL3_IMAGE_INCLUDE_DIR}
        ${SDL3_TTF_INCLUDE_DIR}
)

# -----------------------------
# 6. Link everything together
# -----------------------------
target_link_libraries(game
        frogger_core
        ${SDL3_LIB}
        ${SDL3_IMAGE_LIB}
        ${SDL3_TTF_LIB}
        android
        log
)
