cmake_minimum_required(VERSION 3.29)
project(square_survivors)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
add_executable(square_survivors main.cpp Bullet.h
        Enemy.h Player.h
        EnemyBullet.h
        HighScoreManager.h
        HighScoreManager.cpp
        Utilities.h)
target_link_libraries(square_survivors sfml-graphics sfml-window sfml-system)