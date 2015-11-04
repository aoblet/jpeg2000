#pragma once

#include "Signal1D.hpp"

namespace jpeg2000{
namespace decompose{
namespace AMR{
    Signal1D amr(const Signal1D& in, int level);
    Signal1D iamr(const Signal1D& in, int level);
}
}
}
