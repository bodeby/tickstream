// bench/tickstream/process/heston.cpp

#include <benchmark/benchmark.h>

#include <tickstream/process/price/heston.hpp>

static void BM_Heston(benchmark::State& state)
{
    tickstream::Heston heston({
        .s0 = 100.0,
        .v0 = 0.04,
        .mu = 0.05,
        .kappa = 2.0,
        .theta = 0.04,
        .xi = 0.30,
        .rho = -0.70,
        .dt = 1.0 / 252.0,
        .seed = 42,
    });

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(heston.next());
    }

    state.SetItemsProcessed(state.iterations());

    state.counters["steps/s"] =
        benchmark::Counter(
            state.iterations(),
            benchmark::Counter::kIsRate);
}

BENCHMARK(BM_Heston);

BENCHMARK_MAIN();
