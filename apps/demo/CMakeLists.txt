add_executable(tickstream_demo
    src/main.cpp
)

target_link_libraries(tickstream_demo
    PRIVATE
    tickstream
)
