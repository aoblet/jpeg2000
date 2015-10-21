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
        Signal1D analyseHaar(const Signal1D& signal);
        double mirrorSymmetry(const Signal1D& signal, const int i);

    }
}
#endif //JPEG2000_FILTER_H
