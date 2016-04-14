#pragma once

#include <string>
#include "Signal2D.hpp"

namespace jpeg2000{
namespace decompose{
namespace _2D{
    Signal2D analyse2D_97(const Signal2D& s);
    Signal2D amr(const Signal2D &s, int level);
    Signal2D iamr(const Signal2D &s, int level);
    double quadraticError(const Signal2D &s1, const Signal2D &s2);
    double peakSignalNoiseRatio(const Signal2D &s1, const Signal2D &s2);
}
}
}
