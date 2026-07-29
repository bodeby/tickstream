// apps/server/src/main.cpp

#include "tickstream/process/side/bernoulli.hpp"
#include "transport/sender.hpp"

// library
#include <tickstream/generator.hpp>
#include <tickstream/process/price/gbm.hpp>
#include <tickstream/process/price/heston.hpp>
#include <tickstream/tick.hpp>

// STL
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <span>
#include <thread>

using namespace std::chrono;

int main() {

  // UDP Server Setup

  constexpr auto localhost{"127.0.0.1"};
  constexpr auto max_messages{10'000};
  constexpr auto interval{std::chrono::microseconds(50)};

  transport::Sender sender(localhost, 5000);

  // Tick Generation

  tickstream::BernoulliProcess bernoulli({});

  tickstream::GBM gbm({
    .s0 = 100.0,                             // S0
    .mu = 0.05,                              // drift
    .sigma = 0.20,                           // volatility
    .dt = 1.0 / (252.0 * 6.5 * 60.0 * 60.0), // one second
    .seed = 42,
  });

  tickstream::Heston heston({
    .s0 = 100.0,
    .v0 = 0.04,    // 20% initial volatility (sqrt(0.04) = 0.20)
    .mu = 0.05,    // 5% annual drift
    .kappa = 2.0,  // mean reversion speed
    .theta = 0.04, // long-run variance (20% volatility)
    .xi = 0.30,    // volatility of volatility
    .rho = -0.70,  // leverage effect
    .dt = 1.0 / 252.0,
    .seed = 42,
  });

  tickstream::Generator generator(std::move(gbm));

  // Runtime loop

  // Record starting time
  auto start = high_resolution_clock::now();

  for (std::uint64_t seq{0}; seq < max_messages; ++seq) {
    auto tick = generator.next(seq);
    std::cout << tick << '\n';

    auto bytes = std::as_bytes(std::span{&tick, 1});
    sender.send(bytes);

    std::this_thread::sleep_for(interval);
  };

  // Record ending time
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::cout << "time taken: " << duration.count() << "  ms\n";

  return EXIT_SUCCESS;
}
