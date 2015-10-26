//
// Created by alex on 21/10/15.
//

#ifndef JPEG2000_FILTER_H
#define JPEG2000_FILTER_H

#include "Signal1D.hpp"

namespace jpeg2000 {
    /**
     * Filters used for wavelet transform process.
     */
    namespace filters {

        using namespace std;

        /**
         * Signal interpolation by a factor 2. The returned length signal is multiplied by 2.
         * @param[in] signal to interpolate.
         */
        Signal1D interpole2(const Signal1D& signal);

        /**
         * Signal decimation by a factor 2. The returned length signal is divided by 2.
         * @param[in] signal: to decimate.
         */
        Signal1D decimation2(const Signal1D& signal);

        /**
         * Convolution product on signal with the filter given.
         */
        Signal1D convol(const Signal1D& signal, const Signal1D& filter);

        /**
         * Factorisation of haar process with given filters.
         */
        Signal1D _analyseHaar(const Signal1D& inSignal, const Signal1D& _h0, const Signal1D& _h1 );
        Signal1D _synthesisHaar(const Signal1D& haarSignal, const Signal1D& _g0, const Signal1D& _g1 );

        /**
         * Operates Classic Haar process.
         */
        Signal1D analyseHaar(const Signal1D& signal);
        /**
         * Operates Classic Haar inverse process.
         */
        Signal1D synthesisHaar(const Signal1D& haarSignal);

        /**
         * Operates Classic Haar 9/7 process.
         */
        Signal1D analyseHaar97(const Signal1D& signal);
        /**
         * Operates Classic Haar 9/7 inverse process.
         */
        Signal1D synthesisHaar97(const Signal1D& haarSignal);

        /**
         * Double symmetry operation.
         * @param[in] signal: signal concerned by mirror symmetry
         * @param[in] i: index associated to signal
         * @return A mirror symmetry value.
         */
        double mirrorSymmetry(const Signal1D& signal, const int i);
    }
}
#endif //JPEG2000_FILTER_H
