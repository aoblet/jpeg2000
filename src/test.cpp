//
// Created by alex on 25/10/15.
//

#include "test.hpp"
#include "filters.hpp"
#include <fstream>
#include <string>

namespace jpeg2000{ namespace test{
    void _analyse_sythese_haar(const jpeg2000::Signal1D& in, const std::string& folderOut, bool is97){
        std::string command_mkdir("mkdir -p " + folderOut);
        std::string baseOutPath(folderOut + "/" + in.name() + "_");
        std::string endOutPath(is97 ? "_97" : "");
        endOutPath += ".txt";

        // mkdir the dir folderOut
        system(command_mkdir.c_str());

        std::ofstream fileSignal(baseOutPath + "original" + endOutPath);
        std::ofstream fileSignalAnalyse(baseOutPath + "analyse" + endOutPath);
        std::ofstream fileSignalSynth(baseOutPath + "synth" + endOutPath);

        Signal1D analyse(is97 ? jpeg2000::filters::analyseHaar97(in) : jpeg2000::filters::analyseHaar(in));
        Signal1D synth(is97 ? jpeg2000::filters::synthesisHaar97(analyse) : jpeg2000::filters::synthesisHaar(analyse));

        fileSignal << in;
        fileSignalAnalyse << analyse;
        fileSignalSynth << synth;
    }

    void leleccum_analyse_synthese_haar97() {
        _analyse_sythese_haar(jpeg2000::Signal1D::leleccum(), "haar", true);
    }

    void leleccum_analyse_synthese_haar() {
        _analyse_sythese_haar(jpeg2000::Signal1D::leleccum(), "haar", false);
    }

    void rampe_analyse_synthese_haar97() {
        _analyse_sythese_haar(jpeg2000::Signal1D::rampe(), "haar", true);
    }

    void rampe_analyse_synthese_haar() {
        _analyse_sythese_haar(jpeg2000::Signal1D::rampe(), "haar" ,false);
    }

}}



