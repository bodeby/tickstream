// include/tickstream/consumer.hpp

#pragma once

#include "spsc.hpp"

#include <functional>
#include <thread>
#include <vector>

namespace tickstream {

template <typename T> class Consumer {
public:
  using Handler = std::function<void(const T &)>;

  void subscribe(Handler handler) { handlers_.push_back(handler); }

  void process(SPSC<T> &buffer) {
    T tick;
    while (buffer.try_pop(tick)) {
      for (auto &handler : handlers_) {
        handler(tick);
      }
    }
  }

  void process_continuous(SPSC<T> &buffer, std::atomic<bool> &running) {
    while (running) {
      process(buffer);
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  }

private:
  std::vector<Handler> handlers_;
};

} // namespace tickstream
