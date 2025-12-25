// include/tickstream/stream_manager.hpp

#pragma once
#include <chrono>
#include <iostream>
#include <vector>

namespace tickstream::stream
{
    class StreamManager
    {
    private:
        std::vector<int> streams; // Placeholder for actual stream objects

    public:
        StreamManager() = default; // constructor
        ~StreamManager() = default; // destructor

        // stream container
        void add_stream(int stream) {
            std::cout << "Adding stream" << stream << std::endl;
            streams.push_back(stream);
        };

        void remove_stream() {
            std::cout << "Removing stream: " << std::endl;
            streams.pop_back();
        }

        // stream behaviour
        void start_all() {
            std::cout << "Starting all streams" << std::endl;
            for (const int streamID : streams) {
                std::cout << "my stream" << std::endl;
            }
        };

        void stop_all() {
            std::cout << "Stopping all streams" << std::endl;
            for (const int streamID : streams) {
                std::cout << "Stopping Stream: " << streamID << std::endl;
            }
        };
    };
}
