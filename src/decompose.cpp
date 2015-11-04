#include <cmath>
#include "decompose.hpp"
#include "SignalException.hpp"

namespace jpeg2000{
namespace decompose{
    Signal1D interpole2(const Signal1D &signal) {
        Signal1D interpolated;
        for (double x: signal) {
            interpolated.push_back(x);
            interpolated.push_back(0);
        }
        return interpolated;
    }

    Signal1D decimation2(const Signal1D &signal) {
        Signal1D decimated;
        int halfSize = signal.size() / 2;

        for (int i = 0; i < halfSize; ++i)
            decimated.push_back(signal[i * 2]);
        return decimated;
    }

    Signal1D convol(const Signal1D &signal, const Signal1D &filter) {
        // first check the filter size is odd
        if (!(filter.size() % 2))
            throw jpeg2000::SignalException::Size("convol product: filter must be odd");

        int sizeSignal = signal.size(), sizeFilter = filter.size(), halfSizeFilter = sizeFilter / 2;
        Signal1D filtered(sizeSignal);

        for (int n = 0; n < sizeSignal; ++n) {
            for (int k = -halfSizeFilter; k <= halfSizeFilter; ++k) {
                // handle mirror symmetry
                filtered[n] += filter[k + (halfSizeFilter)] * signal.mirrorSymmetry(n - k);
            }
        }
        return filtered;
    }

    double quadraticError(const Signal1D &s1, const Signal1D &s2) {
        if (s1.size() != s2.size())
            throw jpeg2000::SignalException::Size("quadraticError s1.size() != s2.size()");

        double error = 0;
        for (int i = 0; i < s1.size(); ++i)
            error += std::pow(s1[i] - s2[i], 2);
        return error;
    }
}
}
