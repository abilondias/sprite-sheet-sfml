cmake_minimum_required(VERSION 3.30)
project(sprite_sheet_sfml VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(sprite_sheet_sfml
        src/main.cpp
        src/Movement.h
        src/Player.cpp
        src/Player.h
        src/Background.cpp
        src/Background.h
        src/Camera.cpp
        src/Camera.h
)

file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.3/CPM.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
        EXPECTED_HASH SHA256=cc155ce02e7945e7b8967ddfaff0b050e958a723ef7aad3766d368940cb15494
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

CPMAddPackage("gh:SFML/SFML#3.0.0")
CPMAddPackage("gh:ocornut/imgui#docking")
CPMAddPackage(
        GITHUB_REPOSITORY "eliasdaler/imgui-sfml"
        VERSION "3.0"
        OPTIONS "IMGUI_DIR ${imgui_SOURCE_DIR}"
)
add_compile_definitions(IMGUI_DISABLE_DEMO_WINDOWS) # imgui-sfml doesn't compile demo by default

target_link_libraries(sprite_sheet_sfml PRIVATE SFML::Graphics ImGui-SFML::ImGui-SFML)