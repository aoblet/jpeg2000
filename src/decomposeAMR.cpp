#include "decomposeLifting.hpp"
#include "decomposeAMR.hpp"
#include "SignalException.hpp"
#include "stdexcept"

namespace jpeg2000{
namespace decompose{
namespace AMR{
    Signal1D computeAMR(const Signal1D &signal, int level) {
        if (!signal.isEven())
            throw SignalException::Size("computeAMR: signal is odd");
        if (level < -1)
            throw std::logic_error("computeAMR: level must be greater than 0");

        int maxLevel = maxLevelFromNumber(signal.size());
        if (level == -1)
            level = maxLevel;

        clampLevelToMax(level, maxLevel);
        Signal1D approximatesCoeffs(signal), detailsCoeffs, tmpLifted, tmpDetails;

        // algo recurse to iteratif:

        // 1. compute approximates and details of approximatesCoeff(init: signal itself): lifted97
        // 2. extract details coeffs
        // 3. concat global details to the previous details found at 2.
        // 4. do it again until level is reached
        // 5. return concat detailsCoeffs to approximatesCoeff

        for (int i = 0; i < level; ++i) {
            tmpLifted = std::move(decompose::lifting97::analyseLifting97(approximatesCoeffs));
            approximatesCoeffs = std::move(tmpLifted.extract(0, tmpLifted.size() / 2 - 1));
            tmpDetails = std::move(tmpLifted.extract(tmpLifted.size() / 2));
            detailsCoeffs = std::move(tmpDetails.concat(detailsCoeffs));
        }

        return approximatesCoeffs.concat(detailsCoeffs);
    }

    Signal1D computeIAMR(const Signal1D &amrSignal, int level) {
        if (!amrSignal.isEven())
            throw SignalException::Size("computeIAMR: signal is odd");
        if (level < -1)
            throw std::logic_error("computeIAMR: level must be greater than 0");

        int maxLevel = maxLevelFromNumber(amrSignal.size());
        if(level == -1)
            level = maxLevel;

        clampLevelToMax(level, maxLevel);
        Signal1D tmpUnlifted, tmpSubDetails, reconstructed;

        int sizeAmr = amrSignal.size();
        int maxIter = maxLevelFromNumber(amrSignal.size());
        int indexLimitSubBand = sizeAmr;

        // 1. find which index delimits the "pure" sub band
        // 2. from that one, unlift
        // 3. concat the pre encapsulated details to unlifted signal
        // 4. repeat process from signal obtained at 3.

        for(int i=0; i<level-1; ++i)
            indexLimitSubBand /= 2;
        -- indexLimitSubBand;


        reconstructed = std::move(amrSignal.extract(0, indexLimitSubBand));
        for (int i = 0; i < level - 1; ++i) {
            tmpUnlifted = std::move(decompose::lifting97::synthesisLifting97(reconstructed));
            tmpSubDetails = std::move(amrSignal.extract(tmpUnlifted.size(), tmpUnlifted.size()*2-1));
            reconstructed = std::move(tmpUnlifted.concat(tmpSubDetails));
        }
        // when last turn: no details.
        // so we take out last turn and directly process the synthesisLifting on the entire signal
        reconstructed = std::move(decompose::lifting97::synthesisLifting97(reconstructed));
        return reconstructed;
    }

    int maxLevelFromNumber(int n) {
        int cpt = 0;
        while (!(n % 2) && n > 0) {
            n /= 2;
            ++cpt;
        }
        return cpt;
    }

    void clampLevelToMax(int& level, int max){
        if(level < max)
            return;
        std::cout << "WARNING: AMR compute level greater than max: " << level << " > " << max << std::endl;
        std::cout << "Level set to max " << max << std::endl;
        level = max;
    }
}
}
}