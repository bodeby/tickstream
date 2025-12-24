// include/tickstream/stream_new.hpp

#pragma once
#include <chrono>

namespace tickstream::stream {

    struct Config
    {
        std::chrono::nanoseconds consumer_timeout = std::chrono::milliseconds(100);
    };
    

    class Stream
    {
    public:
        Stream(Config cfg); // constructor
        ~Stream();          // destructor
    };

    // outside defintions
    Stream::Stream(Config cfg){};
    Stream::~Stream(){};
}