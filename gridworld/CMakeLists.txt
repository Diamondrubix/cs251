cmake_minimum_required(VERSION 3.9)
project(gridworld)

set(CMAKE_CXX_STANDARD 11)

add_executable(gridworld t1D_timed.cpp GWInterface.h GridWorld.h _util.h)