#pragma once

#include "Signal1D.hpp"

namespace jpeg2000{
    /**
     * Contains the constants filters.
     */
namespace filters{
    extern const Signal1D ANALYSE_LOW_HAAR;
    extern const Signal1D ANALYSE_HIGH_HAAR;
    extern const Signal1D SYNTHESIS_LOW_HAAR;
    extern const Signal1D SYNTHESIS_HIGH_HAAR;

    extern const Signal1D ANALYSE_LOW_HAAR_97;
    extern const Signal1D ANALYSE_HIGH_HAAR_97;
    extern const Signal1D SYNTHESIS_LOW_HAAR_97;
    extern const Signal1D SYNTHESIS_HIGH_HAAR_97;
}
}
