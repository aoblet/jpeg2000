#pragma once

#include <stdexcept>

namespace jpeg2000{
namespace SignalException{
    class Size : public std::logic_error{
    public:
        using std::logic_error::logic_error;
    };

    class IndexOutOfBounds : public std::logic_error{
    public:
        using std::logic_error::logic_error;
    };
}
}