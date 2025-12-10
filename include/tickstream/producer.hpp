// include/tickstream/producer.hpp

#pragma once

#include <thread>
#include <functional>
#include "ring_buffer.hpp"
#include "tick.hpp"

namespace tickstream {

    template <typename T>
    class Producer;
}
