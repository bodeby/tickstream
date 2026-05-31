# benchmarks/CMakeLists.txt

# ------------------------------------------------------------------
# Google Benchmark Framework
# ------------------------------------------------------------------

include(FetchContent)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.9.5
)

# Disable benchmark's own tests (important)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googlebenchmark)

# ------------------------------------------------------------------
# Discover subdirectories
# ------------------------------------------------------------------

add_subdirectory(tickstream)
