cmake_minimum_required(VERSION 3.16)
project(tickstream LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# header-only library
add_library(tickstream INTERFACE)
target_include_directories(tickstream INTERFACE include)

# thin CLI
add_executable(tickstream_cli src/main.cpp)
target_link_libraries(tickstream_cli PRIVATE tickstream)
