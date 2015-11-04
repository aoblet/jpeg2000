#pragma once

#include "Signal1D.hpp"
#include <string>
#include <boost/filesystem/path.hpp>

namespace jpeg2000{
    /**
     * Performs some tests on decompose.
     */
namespace test{
    /**
     * Process which factorized analyse_haar and reconstruction.
     * The computation is: analyse_haar then synthesis_haar(analyse_haar).
     * It writes the results on txt files according the signal names.
     * @param in: the signal to process.
     * @param folderOut: the folder name to save the results.
     * @param is97: performs 9/7 process or classic if set to false.
     */
    void _analyse_sythese_haar(const jpeg2000::Signal1D &in, const std::string &folderOut, bool is97 = false);

    void _analyse_synthese(const jpeg2000::Signal1D &in, const std::string &folderOut, bool isHaar, bool is97 = false);


    /**
     * Do the analyse and reconstruction onto RAMPE signal. Calls the _analyse_sythese_haar function.
     */
    void rampe_analyse_synthese_haar();

    /**
     * Do the analyse and reconstruction 9/7 onto RAMPE signal. Calls the _analyse_sythese_haar function.
     */
    void rampe_analyse_synthese_haar97();

    /**
     * Do the analyse and reconstruction onto LELECCUM signal. Calls the _analyse_sythese_haar function.
     */
    void leleccum_analyse_synthese_haar();

    /**
     * Do the analyse and reconstruction 9/7 onto LELECCUM signal. Calls the _analyse_sythese_haar function.
     */
    void leleccum_analyse_synthese_haar97();

    void rampe_analyse_synthese_lifting97();
    void leleccum_analyse_synthese_lifting97();
    void lena_haar_haar97_lifting97();
    void _analyse_synthese_lifting97(const Signal1D& in, const std::string& folderOut);
}
}