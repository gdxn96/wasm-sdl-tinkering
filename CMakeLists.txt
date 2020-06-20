cmake_minimum_required(VERSION 3.0.0)
project(wasm-sdl-template VERSION 0.1.0)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    file(TO_CMAKE_PATH "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CMAKE_TOOLCHAIN_FILE)
endif()

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
find_package(SDL2 REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_image)

