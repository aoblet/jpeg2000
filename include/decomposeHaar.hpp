#pragma once

#include "Signal1D.hpp"

namespace jpeg2000{
namespace decompose{
    /**
     * Haar decomposition process: filter bank.
     */
namespace haar{
    /**
     * Factorisation of haar analyse process with given filters.
     * @return A signal with approximate coefficients in the first half and the detail coefficients in the other.
     * @return Under the following form [ ca0, ca1, ..., caN, cd0, cd1, ..., cdN]
     * @param inSignal: Signal to decompose. Even
     * @param _h0: Low pass filter. Odd
     * @param _h1: Low pass filter. Odd
     */
    Signal1D _analyseHaar(const Signal1D &inSignal, const Signal1D &_h0, const Signal1D &_h1);

    /**
     * Factorisation of haar synthesis process with given filters.
     * @return the reconstructed signal from analysed signal i.e analysedSignal param
     * @param analysedSignal: Signal analysed with haar process: contains approximate and details coefficients.
     * @param _g0: Low pass filter. Used on approximate coefficients. Odd
     * @param _g1: High pass filter. Used on details coefficients. Odd
     */
    Signal1D _synthesisHaar(const Signal1D &analysedSignal, const Signal1D &_g0, const Signal1D &_g1);

    /**
     * Operates Classic Haar process.
     * @param signal: Even input signal
     */
    Signal1D analyseHaar(const Signal1D &signal);

    /**
     * Operates Classic Haar inverse process.
     * @param signal: Even input signal. Results of analyseHaar
     */
    Signal1D synthesisHaar(const Signal1D &haarSignal);

    /**
     * Operates Haar 9/7 bi-orthogonal process.
     */
    Signal1D analyseHaar97(const Signal1D &signal);

    /**
     * Operates Haar 9/7 bi-orthogonal inverse process.
     */
    Signal1D synthesisHaar97(const Signal1D &haarSignal);
}
}
}