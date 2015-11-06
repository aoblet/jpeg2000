#pragma once

#include "Signal1D.hpp"

namespace jpeg2000{
namespace decompose{

/**
 * AMR decomposition process: AnalyseMultiResolution decomposition.
 */
namespace AMR{
    /**
     * Compute the analyse multi resolution with a given level.
     * @param signal: Signal to decompose.
     * @param level: Decomposition level
     */
    Signal1D computeAMR(const Signal1D& signal, int level);
    /**
     * Compute the inverse analyse multi resolution with a given level.
     * @param amrSignal: The signal already transformed
     * @param level: Decomposition level
     */
    Signal1D computeIAMR(const Signal1D& amrSignal, int level);
    /**
     * Compute the maximum possible level to use.
     */
    int maxLevelFromNumber(int n);
    /**
     * Clamp the level to max by alerting the user.
     */
    void clampLevelToMax(int& level, int max);
}
}
}
