cmake_minimum_required(VERSION 3.30)
project(sprite_sheet_sfml VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(sprite_sheet_sfml
        main.cpp
        src/Movement.h
        src/Player.cpp
        src/Player.h
        src/Background.cpp
        src/Background.h
        src/Camera.cpp
        src/Camera.h
)

target_link_libraries(sprite_sheet_sfml PRIVATE SFML::Graphics)