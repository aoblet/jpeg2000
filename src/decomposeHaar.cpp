#include "decomposeHaar.hpp"
#include "decompose.hpp"
#include "filters.hpp"
#include <SignalException.hpp>


namespace jpeg2000{
namespace decompose{
namespace haar{
    Signal1D analyseHaar(const Signal1D &signal) {
        const Signal1D  &_h0 = filters::ANALYSE_LOW_HAAR,
                &_h1 = filters::ANALYSE_HIGH_HAAR;
        return _analyseHaar(signal, _h0, _h1);
    }

    Signal1D synthesisHaar(const Signal1D &haarSignal) {
        const Signal1D &_g0 = filters::SYNTHESIS_LOW_HAAR,
                &_g1 = filters::SYNTHESIS_HIGH_HAAR;
        return _synthesisHaar(haarSignal, _g0, _g1);
    }

    Signal1D analyseHaar97(const Signal1D &signal) {
        const Signal1D &_h0 = filters::ANALYSE_LOW_HAAR_97,
                &_h1 = filters::ANALYSE_HIGH_HAAR_97;
        return _analyseHaar(signal, _h0, _h1);
    }


    Signal1D synthesisHaar97(const Signal1D &haarSignal) {
        const Signal1D _g0 = filters::SYNTHESIS_LOW_HAAR_97,
                _g1 = filters::SYNTHESIS_HIGH_HAAR_97;
        return _synthesisHaar(haarSignal, _g0, _g1);
    }

    Signal1D _analyseHaar(const Signal1D &inSignal, const Signal1D &_h0, const Signal1D &_h1) {
        // first check that the signal is even
        if(inSignal.size() % 2)
            throw SignalException::Size("Haar analyse: signal must be even");

        // sld == signalLowPassDecimated
        // shd == signalHighPassDecimated
        Signal1D sld(decimation2(convol(inSignal, _h0))),
                 shd(decimation2(convol(inSignal, _h1)));
        return sld.concat(shd);
    }

    Signal1D _synthesisHaar(const Signal1D &analysedSignal, const Signal1D &_g0, const Signal1D &_g1) {
        // first check that the signal is even
        if(analysedSignal.size() % 2)
            throw SignalException::Size("Haar synthesis: analysed signal must be even");

        Signal1D approximateCoeffs(analysedSignal.extract(0, analysedSignal.size() / 2 - 1));
        Signal1D detailsCoeffs(analysedSignal.extract(analysedSignal.size() / 2));

        // sli == Signal LowPass  Interpolated
        // shi == Signal HighPass Interpolated
        Signal1D sli(convol(interpole2(approximateCoeffs), _g0)),
                 shi(convol(interpole2(detailsCoeffs), _g1));
        return sli += shi;  // reconstructed signal
    }
}
}
}
