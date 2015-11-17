#pragma once

#include <stdexcept>

namespace jpeg2000{
namespace SignalException{
    class Size : public std::logic_error{
    public:
        using std::logic_error::logic_error;
    };

    class OutOfRange : public std::out_of_range{
    public:
        using std::out_of_range::out_of_range;
    };
}
}