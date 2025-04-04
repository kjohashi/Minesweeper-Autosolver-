cmake_minimum_required(VERSION 3.29)
project(MinesweeperRecursion)

set(CMAKE_CXX_STANDARD 20)

add_executable(MinesweeperRecursion main.cpp
        View.cpp
        Controller.h
        Model.cpp
        Controller.cpp)

target_link_libraries(MinesweeperRecursion sfml-graphics sfml-audio)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)