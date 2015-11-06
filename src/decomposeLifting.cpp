
#include "decomposeLifting.hpp"
#include "SignalException.hpp"

namespace jpeg2000{
namespace decompose{
namespace lifting97{

    void predictionLifting97(double a, Signal1D &signal) {
        for (int i = 0; i < signal.size() / 2; ++i)
            signal[2 * i + 1] = a * signal.mirrorSymmetry(2 * i) + signal.mirrorSymmetry(2 * i + 1) +
                                a * signal.mirrorSymmetry(2 * i + 2);
    }

    void updateLifting97(double a, Signal1D &signal) {
        for (int i = 0; i < signal.size() / 2; ++i)
            signal[2 * i] = a * signal.mirrorSymmetry(2 * i - 1) + signal.mirrorSymmetry(2 * i) +
                            a * signal.mirrorSymmetry(2 * i + 1);
    }

    void scaleLifting97(double a, Signal1D &signal) {
        for (int i = 0; i < signal.size() / 2; ++i) {
            signal[2 * i] /= a;
            signal[2 * i + 1] *= a;
        }
    }

    Signal1D analyseLifting97(const Signal1D &signal) {
        // signal must be even
        if (!signal.isEven())
            throw jpeg2000::SignalException::Size("analyseLifting97: signal must be even");

        Signal1D analysed(signal);

        // first prediction: on odd values
        predictionLifting97(lifting97::constants::PREDICTION_FIRST_COEFF, analysed);
        // first maj: on even values
        updateLifting97(lifting97::constants::UPDATE_FIRST_COEFF, analysed);
        // second prediction: on odd values
        predictionLifting97(lifting97::constants::PREDICTION_SECOND_COEFF, analysed);
        // second maj: on even values
        updateLifting97(lifting97::constants::UPDATE_SECOND_COEFF, analysed);
        // scaling
        scaleLifting97(1 / lifting97::constants::SCALING_COEFF, analysed);

        // order even to first part, odd to the other half: approximate and details coefficients
        Signal1D ordered;
        for (int i = 0; i < analysed.size() / 2; ++i)
            ordered.push_back(analysed[2 * i]);
        for (int i = 0; i < analysed.size() / 2; ++i)
            ordered.push_back(analysed[2 * i + 1]);

        return ordered;
    }

    Signal1D synthesisLifting97(const Signal1D &liftedSignal) {
        // signal must be even
        if (!liftedSignal.isEven())
            throw jpeg2000::SignalException::Size("synthesisLifting97: signal must be even");

        Signal1D synthesis;
        int halfSize_liftedSignal = liftedSignal.size() / 2;

        for (int i = 0; i < halfSize_liftedSignal; ++i) {
            synthesis.push_back(liftedSignal[i]);
            synthesis.push_back(liftedSignal[halfSize_liftedSignal + i]);
        }

        // reverse lifting process
        // un-scaling
        scaleLifting97(lifting97::constants::SCALING_COEFF, synthesis);
        // second maj: on even values
        updateLifting97(-lifting97::constants::UPDATE_SECOND_COEFF, synthesis);
        // second prediction: on odd values
        predictionLifting97(-lifting97::constants::PREDICTION_SECOND_COEFF, synthesis);
        // first maj: on even values
        updateLifting97(-lifting97::constants::UPDATE_FIRST_COEFF, synthesis);
        // first prediction: on odd values
        predictionLifting97(-lifting97::constants::PREDICTION_FIRST_COEFF, synthesis);

        return synthesis;
    }
}
}
}