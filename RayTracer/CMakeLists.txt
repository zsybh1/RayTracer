cmake_minimum_required(VERSION 3.0.0)
project(ray-tracing-in-one-week VERSION 0.1.0)

include_directories(include)
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O3")

add_executable(ray-tracing-in-one-week main.cpp)