cmake_minimum_required(VERSION 3.16)
project(tickstream LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# header-only library
add_library(tickstream INTERFACE)
target_include_directories(tickstream INTERFACE include)

# thin CLI
add_executable(tickstream_cli src/main.cpp)
target_link_libraries(tickstream_cli PRIVATE tickstream)

# single stream example
# add_executable(single_stream_example src/single_stream.cpp)
# target_link_libraries(single_stream_example PRIVATE tickstream)

# ------------------ TEST SUITE ------------------

add_executable(tests
    external/catch2/catch_amalgamated.cpp  # The catch implementation
    tests/tickstream/test_tick.cpp
)

# Include directories for tests
target_include_directories(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/catch2  # catch_amalgamated.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include          # project headers
)

# Link test executable with your libraries
target_link_libraries(tests PRIVATE tickstream)

# Enable CTest
enable_testing()
add_test(NAME tests COMMAND tests)

# Optional: Add a test target for easy building
add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS tests
    COMMENT "Running tests..."
)