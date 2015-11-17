#pragma once

#include <string>
#include "Signal2D.hpp"

namespace jpeg2000{
namespace decompose{
namespace _2D{
    Signal2D analyse2D_97(const Signal2D& s);
    Signal2D amr(const Signal2D &s, int level);
    Signal2D iamr(const Signal2D &s, int level);
}
}
}
