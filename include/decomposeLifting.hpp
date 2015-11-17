#pragma once

#include "Signal1D.hpp"

namespace jpeg2000{
namespace decompose{
    /**
     * Lifting 9/7 bi-orthogonal decompose process.
     * The lifting process is faster than haar decomposition: there are less operations.
     */
namespace lifting97{
    /**
     * Operates the lifting analyse process.
     * Does several consecutive operations to obtain the lifted signal by using prediction,
     * update and scaling tools.
     * @param signal: Even input signal
     */
    Signal1D analyseLifting97(const Signal1D& signal);
    /**
     * Operates the synthesis process from a lifted signal.
     * @param liftedSignal: Even signal resulting of lifting process.
     * @return The reconstructed signal.
     */
    Signal1D synthesisLifting97(const Signal1D& liftedSignal);
    /**
     * Intermediate lifting tool.
     * From a given signal it changes the odd values: details coefficients: kind of convolution.
     * @param a: Lifting prediction coefficient
     * @param[in] signal: Even input signal to process on
     * @param[out] signal The result is written in it
     */
    void predictionLifting97(double a, Signal1D& signal);
    /**
     * Intermediate lifting tool.
     * From a given signal it changes the even values: approximate coefficients: kind of convolution.
     * @param a: Lifting update coefficient
     * @param[in] signal: Even input signal to process on.
     * @param[out] signal The result is written in it
     */
    void updateLifting97(double a, Signal1D& signal);
    /**
     * Intermediate lifting tool.
     * From a given signal it scales the lifted coefficients.
     * It divides the even values by a and multiply the odd values by a
     * @param a: Lifting scale coefficient
     * @param[in] signal: Even input signal to process on.
     * @param[out] signal The result is written in it
     */
    void scaleLifting97(double a, Signal1D& signal);

namespace constants{
    const double PREDICTION_FIRST_COEFF = -1.586134342;
    const double PREDICTION_SECOND_COEFF = 0.8829110762;

    const double UPDATE_FIRST_COEFF = -0.05298011854;
    const double UPDATE_SECOND_COEFF = 0.4435068522;

    const double SCALING_COEFF = 1.149604398;
}
}
}
}