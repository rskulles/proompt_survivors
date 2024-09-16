cmake_minimum_required(VERSION 3.29)
project(square_survivors)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS CACHE "" OFF)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
)

FetchContent_MakeAvailable(SFML)
set(SFML_STATIC_LIBRARIES TRUE)
add_definitions(-DSFML_STATIC)
add_executable(square_survivors main.cpp Bullet.h
        Enemy.h Player.h
        EnemyBullet.h
        HighScoreManager.h
        HighScoreManager.cpp
        Utilities.h)
target_link_libraries(square_survivors sfml-graphics sfml-window sfml-system)

if (WIN32)
    target_link_libraries(square_survivors ws2_32 opengl32 freetype jpeg)
endif ()