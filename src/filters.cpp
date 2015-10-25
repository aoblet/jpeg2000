#include <cmath>
#include "filters.hpp"
#include <algorithm>

namespace jpeg2000{ namespace filters{
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
            decimated.push_back(signal[i << 1]); // <<1 == *2
        return decimated;
    }

    Signal1D convol(const Signal1D &signal, const Signal1D &filter) {
        int sizeSignal = signal.size(), sizeFilter = filter.size(), halfSizeFilter = sizeFilter/2;
        Signal1D filtered(sizeSignal);

        for (int n = 0; n < sizeSignal; ++n) {
            for (int k = -halfSizeFilter; k < halfSizeFilter; ++k) {
                // handle mirror symmetry
                filtered[n] += filter[k + (halfSizeFilter)] * mirrorSymmetry(signal, n - k);
            }
        }
        return filtered;
    }

    double mirrorSymmetry(const Signal1D &signal, const int i) {
        if (i < -1)
            return signal[i * -1];
        if (i > signal.size() - 1)
            return signal[2 * signal.size() - i + 1];
        return signal[i];
    }

    Signal1D analyseHaar(const Signal1D &signal) {
        // sld == signalLowPassDecimated
        // shd == signalHighPassDecimated
        Signal1D _h0{1.0 / sqrt(2), 1.0 / sqrt(2), 0},
                 _h1{1.0 / sqrt(2), -1.0 / sqrt(2), 0};

        return _analyseHaar(signal, _h0, _h1);
    }

    Signal1D synthesisHaar(const Signal1D &haarSignal) {
        Signal1D _g0{0, 1.0 / sqrt(2), 1.0 / sqrt(2)},
                 _g1{0, -1.0 / sqrt(2), 1.0 / sqrt(2)};

        return _synthesisHaar(haarSignal, _g0, _g1);
    }

    Signal1D analyseHaar97(const Signal1D &signal) {
        Signal1D _h0,_h1;
        // Filtre biorthogonal 9/7 _h0 (longueur 9)
        _h0.push_back(0.037828455507  );
        _h0.push_back(-0.023849465019 );
        _h0.push_back(-0.110624404418 );
        _h0.push_back(0.377402855613  );
        _h0.push_back(0.852698679009  );
        _h0.push_back(0.377402855613  );
        _h0.push_back(-0.110624404418 );
        _h0.push_back(-0.023849465019 );
        _h0.push_back(0.037828455507  );

        // Filtre biorthogonal 9/7 _h1 (longueur 9)
        _h1.push_back(0.064538882629 );
        _h1.push_back(-0.040689417610);
        _h1.push_back(-0.418092273222);
        _h1.push_back(0.788485616406 );
        _h1.push_back(-0.418092273222);
        _h1.push_back(-0.040689417610);
        _h1.push_back(0.064538882629 );
        _h1.push_back(0.000000000000 );
        _h1.push_back(-0.000000000000);
        return _analyseHaar(signal, _h0, _h1);
    }


    Signal1D synthesisHaar97(const Signal1D &haarSignal) {
        Signal1D _g0,_g1;

        // Filtre biorthogonal 9/7 _g0 (longueur 7)
        _g0.push_back(-0.064538882629);
        _g0.push_back(-0.040689417610);
        _g0.push_back(0.418092273222 );
        _g0.push_back(0.788485616406 );
        _g0.push_back(0.418092273222 );
        _g0.push_back(-0.040689417610);
        _g0.push_back(-0.064538882629);

        // Filtre biorthogonal 9/7 _g1 (longueur 11)
        _g1.push_back(0.000000000000 );
        _g1.push_back(-0.000000000000);
        _g1.push_back(0.037828455507 );
        _g1.push_back(0.023849465019 );
        _g1.push_back(-0.110624404418);
        _g1.push_back(-0.377402855613);
        _g1.push_back(0.852698679009 );
        _g1.push_back(-0.377402855613);
        _g1.push_back(-0.110624404418);
        _g1.push_back(0.023849465019 );
        _g1.push_back(0.037828455507 );
        return _synthesisHaar(haarSignal, _g0, _g1);
    }

    Signal1D _analyseHaar(const Signal1D &inSignal, const Signal1D &_h0, const Signal1D &_h1) {
        // sld == signalLowPassDecimated
        // shd == signalHighPassDecimated
        Signal1D sld(decimation2(convol(inSignal, _h0))),
                 shd(decimation2(convol(inSignal, _h1)));
        return sld + shd;
    }

    Signal1D _synthesisHaar(const Signal1D &haarSignal, const Signal1D &_g0, const Signal1D &_g1) {
        // sbi == signalLowPassInterpolated
        // shi == signalHighPassInterpolated
        Signal1D sli(interpole2(convol(haarSignal, _g0))),
                 shi(interpole2(convol(haarSignal, _g1))),
                 reconstructedSignal;

        reconstructedSignal = sli;
        std::transform(reconstructedSignal.begin(), reconstructedSignal.end(), shi.begin(), shi.begin(), std::plus<double>());
        return reconstructedSignal;

    }
}
}
