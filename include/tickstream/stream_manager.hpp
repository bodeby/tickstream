// include/tickstream/stream_manager.hpp

#pragma once
#include <chrono>

namespace tickstream::stream
{
    class StreamManager
    {
    public:
        StreamManager();    // constructor
        ~StreamManager();   // destructor

        // stream container
        void add_stream();
        void remove_stream();

        // stream behaviour
        void start_all();
        void stop_all();

    };

    // outside definitions
    StreamManager::StreamManager() {};
    StreamManager::~StreamManager() {};


    void StreamManager::add_stream() {};
    void StreamManager::remove_stream() {};

    void StreamManager::start_all(){};
    void StreamManager::stop_all(){}


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
