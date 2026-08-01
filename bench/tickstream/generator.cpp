// bench/tickstream/generator/gbm.cpp

#include <benchmark/benchmark.h>

#include <tickstream/generator.hpp>
#include <tickstream/process/price/gbm.hpp>

static void BM_GeneratorGBM(benchmark::State& state)
{
    tickstream::GBM gbm({
        .s0 = 100.0,
        .mu = 0.05,
        .sigma = 0.20,
        .dt = 1.0 / 252.0,
        .seed = 42,
    });

    tickstream::Generator generator(std::move(gbm));

    std::uint64_t seq = 0;

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(generator.next(seq++));
    }

    state.SetItemsProcessed(state.iterations());

    state.counters["ticks/s"] =
        benchmark::Counter(
            state.iterations(),
            benchmark::Counter::kIsRate);
}

BENCHMARK(BM_GeneratorGBM);
BENCHMARK_MAIN();
