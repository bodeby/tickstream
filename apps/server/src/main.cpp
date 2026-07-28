// apps/server/src/main.cpp

#include "transport/sender.hpp"

// library
#include <iostream>
#include <random>
#include <tickstream/core/tick.hpp>
#include <tickstream/process/gbm.hpp>

// STL
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <thread>

int main() {

  // UDP Server Setup

  constexpr auto localhost = "127.0.0.1";
  constexpr auto max_messages{10'000};
  constexpr auto interval = std::chrono::milliseconds(1);

  transport::Sender sender(localhost, 5000);

  // Tick Generation

  tickstream::GBM price({
    .s0 = 100.0,                            // S0
    .mu = 0.05,                             // drift
    .sigma = 0.20,                          // volatility
    .dt = 1.0 / (252.0 * 6.5 * 60.0 * 60.0) // one second
  });

  auto tick = tickstream::core::Tick{};

  // distributions

  std::mt19937_64 rng(42);
  std::poisson_distribution<std::uint32_t> qty_dist(10);
  std::discrete_distribution<std::uint8_t> type_dist({80, 15, 5});
  std::bernoulli_distribution side_dist(0.5);

  // Runtime loop

  for (std::uint64_t i{0}; i < max_messages; ++i) {

    tick.seq = i;
    tick.exchange_ts = 0;       // _rdtsc
    tick.price = price.next();  // process based
    tick.symbol = 999;          // static, we dont need multi for now
    tick.qty = qty_dist(rng);   // process based maybe Heston or OU
    tick.side = side_dist(rng); // distribution: maybe bernoulli
    tick.type = type_dist(rng); //should repr:  Trade, Quote, Update via uint8

    std::cout << "tick: " << tick << '\n';

    auto bytes = std::as_bytes(std::span{&tick, 1});
    sender.send(bytes);

    std::this_thread::sleep_for(interval);
  };

  return EXIT_SUCCESS;
}
