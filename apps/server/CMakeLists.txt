add_executable(tickstream_server
    src/main.cpp
    src/transport/sender.cpp
)

target_link_libraries(tickstream_server
    PRIVATE
    tickstream
)
