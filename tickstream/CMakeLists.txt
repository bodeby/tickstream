cmake_minimum_required(VERSION 3.20)

# ------------------------------------------------------------------
# Core library (venue-agnostic runtime + business logic)
# ------------------------------------------------------------------

add_library(tickstream STATIC)

target_include_directories(tickstream
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(tickstream
    PUBLIC
        cxx_std_20
)

target_compile_options(tickstream
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wsign-conversion
)
