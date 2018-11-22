cmake_minimum_required(VERSION 3.12)
project(SimplePhysicsSimulation)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package (Qt5Widgets REQUIRED)
find_package (Qt5Gui REQUIRED)
find_package (Qt5Core REQUIRED)

add_executable(SimplePhysicsSimulation main.cpp Simulator/Simulator.h SimObjects/Circle.h SimObjects/Rectangle.h  SimObjects/SimObject.cpp SimObjects/SimObject.cpp SimObjects/SimObject.h Points/PointsOperations.cpp Points/PointsOperations.h SimObjects/Circle.cpp SimObjects/Rectangle.cpp Simulator/Simulator.cpp Simulator/Simulator.h)
qt5_use_modules(SimplePhysicsSimulation Widgets)
qt5_use_modules(SimplePhysicsSimulation Gui)
qt5_use_modules(SimplePhysicsSimulation Core)
