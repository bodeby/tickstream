// apps/demo/main.cpp

#include <cstdlib>
#include <iostream>
#include <ostream>

// internal includes
#include <tickstream/consumer.hpp>
#include <tickstream/core/ring_buffer.hpp>
#include <tickstream/params.hpp>
#include <tickstream/producer.hpp>
#include <tickstream/stream_gen.hpp>
#include <tickstream/tick.hpp>

namespace ts = tickstream; // local alias

using TickBuffer = ts::RingBuffer<ts::Tick>; // semantic alias
using TickConsumer = ts::Consumer<ts::Tick>; // semantic alias
using TickProducer = ts::Producer<ts::Tick>; // semantic alias

constexpr static auto buf_size = 2 << 9;

int main() {
  TickBuffer ring_buffer(buf_size);
  TickConsumer consumer();
  TickProducer producer();

  auto tick_1 = ts::tick_btc();
  auto tick_2 = ts::tick_btc();

  std::cout << tick_1 << "\n";
  std::cout << tick_2 << "\n";

  bool pushed_1 = ring_buffer.try_push(tick_1);
  bool pushed_2 = ring_buffer.try_push(tick_2);

  std::cout << "Pushed BTC tick: " << (pushed_1 ? "success" : "failure")
            << "\n";
  std::cout << "Pushed ETH tick: " << (pushed_2 ? "success" : "failure")
            << "\n";
  std::cout << "Ring buffer size after pushes: " << ring_buffer.size() << "\n";

  bool popped_1 = ring_buffer.try_pop(tick_1);
  bool popped_2 = ring_buffer.try_pop(tick_2);

  std::cout << "Popped BTC tick: " << (popped_1 ? "success" : "failure")
            << "\n";
  std::cout << "Popped ETH tick: " << (popped_2 ? "success" : "failure")
            << "\n";
  std::cout << "Ring buffer size after pops: " << ring_buffer.size() << "\n";

  bool pushed_3 = ring_buffer.try_push(tick_1);

  if (!pushed_3) {
    return EXIT_FAILURE;
  }

  ring_buffer.clear(); // Clear the buffer

  std::cout << "Ring buffer size after clear: " << ring_buffer.size() << "\n";
  std::cout << "Popped tick price: " << tick_1.price << "\n";

  return EXIT_SUCCESS;
};
