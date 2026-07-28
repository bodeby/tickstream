// apps/server/src/main.cpp

#include "transport/sender.hpp"

// library
#include <tickstream/generator.hpp>
#include <tickstream/process/gbm.hpp>
#include <tickstream/process/heston.hpp>
#include <tickstream/tick.hpp>

// STL
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
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

  tickstream::Heston price_2({
    .s0 = 100.0,                            // S0
    .mu = 0.05,                             // drift
    .sigma = 0.20,                          // volatility
    .dt = 1.0 / (252.0 * 6.5 * 60.0 * 60.0) // one second
  });

  tickstream::Generator generator(std::move(price_2));

  // Runtime loop

  for (std::uint64_t seq{0}; seq < max_messages; ++seq) {
    auto tick = generator.next(seq);
    std::cout << "tick: " << tick << '\n';

    auto bytes = std::as_bytes(std::span{&tick, 1});
    sender.send(bytes);

    std::this_thread::sleep_for(interval);
  };

  return EXIT_SUCCESS;
}
