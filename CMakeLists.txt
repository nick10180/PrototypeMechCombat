cmake_minimum_required(VERSION 3.23)
project(PrototypeMechCombat)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-static")
add_executable(PrototypeMechCombat main.cpp engine.h controllerplayerimps.cpp)
