//
// Created by alex on 21/10/15.
//

#ifndef JPEG2000_FILTER_H
#define JPEG2000_FILTER_H

#include "Signal1D.hpp"

namespace jpeg2000 {
    namespace filters {
        using namespace std;

        Signal1D interpole2(const Signal1D& signal);
        Signal1D decimation2(const Signal1D& signal);
        Signal1D convol(const Signal1D& signal, const Signal1D& filter);

        Signal1D _analyseHaar(const Signal1D& inSignal, const Signal1D& _h0, const Signal1D& _h1 );
        Signal1D _synthesisHaar(const Signal1D& haarSignal, const Signal1D& _g0, const Signal1D& _g1 );
        Signal1D analyseHaar(const Signal1D& signal);
        Signal1D synthesisHaar(const Signal1D& haarSignal);
        Signal1D analyseHaar97(const Signal1D& signal);
        Signal1D synthesisHaar97(const Signal1D& haarSignal);
        double mirrorSymmetry(const Signal1D& signal, const int i);

    }
}
#endif //JPEG2000_FILTER_H
