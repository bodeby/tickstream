cmake_minimum_required(VERSION 3.20)

project(tickstream LANGUAGES CXX)

# ------------------------------------------------------------------
# Header-only library
# ------------------------------------------------------------------

add_library(tickstream INTERFACE)

target_include_directories(tickstream
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(tickstream
    INTERFACE
        cxx_std_20
)

target_compile_options(tickstream
    INTERFACE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wsign-conversion
)
