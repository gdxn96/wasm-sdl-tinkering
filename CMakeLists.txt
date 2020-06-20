cmake_minimum_required(VERSION 3.0.0)
project(wasm-sdl-template VERSION 0.1.0)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    file(TO_CMAKE_PATH "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CMAKE_TOOLCHAIN_FILE)
endif()

add_executable(wasm-sdl-template main.cpp)
find_package(SDL2 REQUIRED)
target_link_libraries(wasm-sdl-template SDL2::SDL2 SDL2::SDL2main)
