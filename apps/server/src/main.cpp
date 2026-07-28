// apps/server/src/main.cpp

#include "transport/sender.hpp"

// library
#include <iostream>
#include <tickstream/core/tick.hpp>
#include <tickstream/process/gbm.hpp>

// STL
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <format>
#include <span>
#include <thread>

int main() {

  // UDP Server Setup

  constexpr auto localhost = "127.0.0.1";
  constexpr auto max_messages{10'000};
  constexpr auto interval = std::chrono::milliseconds(1);

  transport::Sender sender(localhost, 5000);

  // Tick Generation

  tickstream::GBM process({
    .s0 = 100.0,                            // S0
    .mu = 0.05,                             // drift
    .sigma = 0.20,                          // volatility
    .dt = 1.0 / (252.0 * 6.5 * 60.0 * 60.0) // one second
  });

  auto tick = tickstream::core::Tick{
    .seq = 0,
    .exchange_ts = 0,
    .symbol = 999,
    .price = 10,
    .qty = 10,
    .side = 0,
    .type = 0,
    .reserved = 0,
  };

  // Runtime loop

  for (std::uint64_t i{0}; i < max_messages; ++i) {

    auto message = std::format("UDP message: {}\n", i);
    tick.seq = i;

    std::cout << "Hello from GBM: " << process.next() << '\n';

    auto bytes = std::as_bytes(std::span{&tick, 1});
    sender.send(bytes);

    std::this_thread::sleep_for(interval);
  };

  return EXIT_SUCCESS;
}
