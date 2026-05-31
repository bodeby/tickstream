# ------------------------------------------------------------------
# Projects settings (applies to all targets)
# ------------------------------------------------------------------
#
# Build type, compiler, and sanitizers are configured via presets

project(tickstream LANGUAGES CXX)
cmake_minimum_required(VERSION 3.20)

# ------------------------------------------------------------------
# Global language settings (applies to all targets)
# ------------------------------------------------------------------
#
# Build type, compiler, and sanitizers are configured via presets

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------------
# Core libraries
# ------------------------------------------------------------------
#
# Venue-agnostic runtime, recorder and protocol code

add_subdirectory(tickstream)

# ------------------------------------------------------------------
# Vendor libraries
# ------------------------------------------------------------------

# add_subdirectory(vendor)

# ------------------------------------------------------------------
# Applications
# ------------------------------------------------------------------
#
# Executables that wire libraries together (entry points only)

set(TS_BUILD_APPS_DEFAULT ON)

option(TS_BUILD_TRADER "Build demo app" ${TS_BUILD_APPS_DEFAULT})

if (TS_BUILD_DEMO)
  add_subdirectory(apps/demo) # main entry
endif()

# ------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------

option(TS_BUILD_TESTS "Build unit tests" OFF)

if (TS_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

# ------------------------------------------------------------------
# Benchmarks
# ------------------------------------------------------------------

option(TS_BUILD_BENCHMARKS "Build benchmarks" OFF)

if (TS_BUILD_BENCHMARKS)
  add_subdirectory(benchmarks)
endif()
