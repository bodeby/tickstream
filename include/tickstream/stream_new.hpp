// include/tickstream/stream_new.hpp

#pragma once
#include <chrono>

namespace tickstream::stream
{

    struct Config
    {
        std::chrono::nanoseconds consumer_timeout = std::chrono::milliseconds(100);
    };

    class Stream
    {
    private:
        Config conf;

    public:
        Stream(Config cfg) : conf(cfg) {}; // constructor
        ~Stream() = default;               // destructor
    };
}