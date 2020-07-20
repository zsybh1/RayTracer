cmake_minimum_required(VERSION 3.0.0)
project(ray-tracing-in-one-week VERSION 0.1.0)

include_directories(include)
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -static")

add_executable(ray-tracing main.cpp)