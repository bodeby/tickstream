// tickstream/process/process.hpp

#pragma once

namespace tickstream {

template <typename T>
class Process {
public:
    using value_type = T;

    virtual ~Process() = default;
    virtual T next() = 0;
};

} // namespace tickstream::process
