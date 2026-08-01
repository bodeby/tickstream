# ------------------------------------------------------------------
# Projects settings (applies to all targets)
# ------------------------------------------------------------------
#
# Build type, compiler, and sanitizers are configured via presets

cmake_minimum_required(VERSION 3.20)
project(tickstream LANGUAGES CXX)

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

option(TS_BUILD_DEMO       "Build demo app"      OFF)
option(TS_BUILD_SERVER     "Builder server app"  ON)
option(TS_BUILD_BENCHMARKS "Build benchmarks"    ON)

if (TS_BUILD_DEMO)
  add_subdirectory(apps/demo) # main entry
endif()

if (TS_BUILD_SERVER)
  add_subdirectory(apps/server)
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
  add_subdirectory(bench)
endif()
