add_executable(gbm_benchmark
    process/gbm.cpp
)

target_link_libraries(gbm_benchmark
    PRIVATE
        tickstream
        benchmark::benchmark_main
)

add_executable(heston_benchmark
    process/heston.cpp
)

target_link_libraries(heston_benchmark
    PRIVATE
        tickstream
        benchmark::benchmark_main
)

# generator

add_executable(generator_benchmark
    generator.cpp
)

target_link_libraries(generator_benchmark
    PRIVATE
        tickstream
        benchmark::benchmark_main
)
