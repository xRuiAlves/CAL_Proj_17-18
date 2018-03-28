cmake_minimum_required(VERSION 3.9)
project(CAL)

set(CMAKE_CXX_STANDARD 11)

include_directories(cute_lib)

file(GLOB_RECURSE SOURCE_FILES "src/*/*.cpp")

add_executable(CAL ${SOURCE_FILES} src/Algorithms/AStar.cpp src/Algorithms/AStar.h src/Algorithms/Dijkstra.cpp src/Graph/ANode.cpp src/Graph/ANode.h)