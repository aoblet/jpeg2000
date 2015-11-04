#pragma once
#include "Signal1D.hpp"

namespace jpeg2000 {
    /**
     * Decomposition tools used for wavelet transform process.
     */
namespace decompose{

    /**
     * Signal interpolation by a factor 2. The returned length signal is multiplied by 2.
     * @param signal to interpolate.
     * @return: The interpolated signal.
     */
    Signal1D interpole2(const Signal1D &signal);

    /**
     * Signal decimation by a factor 2. The returned length signal is divided by 2.
     * @param signal: Signal to decimate. Even.
     * @return: The decimated signal.
     */
    Signal1D decimation2(const Signal1D &signal);

    /**
     * Convolution product on signal with the filter given.
     * @param signal: Even.
     * @param filter: Odd.
     */
    Signal1D convol(const Signal1D &signal, const Signal1D &filter);

    /**
     * Compute the quadratic error between two signals.
     * The two signals length must be equals.
     */
    double quadraticError(const Signal1D& s1, const Signal1D& s2);
}
}
