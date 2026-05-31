// apps/demo/main.cpp

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>

// internal includes
#include <tickstream/generator.hpp>
#include <tickstream/params.hpp>
#include <tickstream/tick.hpp>
#include <tickstream/transport/consumer.hpp>
#include <tickstream/transport/producer.hpp>
#include <tickstream/transport/ring_buffer.hpp>

namespace ts = tickstream; // local alias

using TickBuffer = ts::RingBuffer<ts::Tick>; // semantic alias
using TickConsumer = ts::Consumer<ts::Tick>; // semantic alias
using TickProducer = ts::Producer<ts::Tick>; // semantic alias

constexpr static std::size_t buffer_size{1024};

int main() {
  TickBuffer ring_buffer(buffer_size);
  TickConsumer consumer();
  TickProducer producer();

  auto tick_1 = ts::tick_btc();
  auto tick_2 = ts::tick_btc();

  std::cout << tick_1 << "\n";
  std::cout << tick_2 << "\n";

  ring_buffer.try_push(tick_1);
  ring_buffer.try_push(tick_2);

  std::cout << "Ring buffer size after pushes: " << ring_buffer.size() << "\n";

  ring_buffer.try_pop(tick_1);
  ring_buffer.try_pop(tick_2);

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
