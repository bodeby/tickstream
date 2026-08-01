// bench/tickstream/process/gbm.cpp

#include <benchmark/benchmark.h>

#include <tickstream/process/price/gbm.hpp>

static void BM_GBM(benchmark::State& state)
{
    tickstream::GBM gbm({
        .s0 = 100.0,
        .mu = 0.05,
        .sigma = 0.2,
        .dt = 1.0 / 252.0,
        .seed = 42,
    });

    for (auto _ : state)
    {
        auto price = gbm.next();
        benchmark::DoNotOptimize(price);
    }
}

BENCHMARK(BM_GBM);

BENCHMARK_MAIN();
