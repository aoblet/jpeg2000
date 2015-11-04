#include "test.hpp"
#include "decompose.hpp"
#include "decomposeHaar.hpp"
#include "decomposeLifting.hpp"
#include "assets.hpp"

#include <fstream>
#include <algorithm>
#include <assets.hpp>


namespace jpeg2000{ namespace test{
    void _analyse_synthese(const jpeg2000::Signal1D &in, const std::string &folderOut, bool isHaar, bool is97){
        std::string command_mkdir("mkdir -p " + folderOut);
        std::string baseOutPath(folderOut + "/" + in.name() + "_");
        std::string endOutPath(is97 ? "_97" : "");
        endOutPath += ".txt";

        // mkdir the dir folderOut
        system(command_mkdir.c_str());

        // we save the different signals to compare
        std::ofstream fileSignal(baseOutPath + "original" + endOutPath);
        std::ofstream fileSignalAnalyse(baseOutPath + "analyse" + endOutPath);
        std::ofstream fileSignalSynth(baseOutPath + "synth" + endOutPath);

        Signal1D analyse;
        Signal1D synth;

        if(isHaar){
            analyse = is97 ? decompose::haar::analyseHaar97(in) : decompose::haar::analyseHaar(in);
            synth = is97 ? decompose::haar::synthesisHaar97(analyse) : decompose::haar::synthesisHaar(analyse) ;
        }
        else{
            analyse = decompose::lifting97::analyseLifting97(in);
            synth = decompose::lifting97::synthesisLifting97(analyse);
        }

        fileSignal << in;
        fileSignalAnalyse << analyse;
        fileSignalSynth << synth;

        std::cout << "********* QUADRATIC ERROR ********** " << std::endl;
        std::cout << "Parameters: ";
        std::cout << in.name() << " isHaar " << (isHaar ? "yes" : "no") << ", is97 " << (is97 ? "yes" : "no") << std::endl;
        std::cout << "Error = " << decompose::quadraticError(in, synth) << std::endl;
        std::cout << "--------------------" << std::endl << std::endl;
    }

    void _analyse_sythese_haar(const jpeg2000::Signal1D& in, const std::string& folderOut, bool is97){
        _analyse_synthese(in, folderOut, true, is97);
    }

    void leleccum_analyse_synthese_haar97() {
        _analyse_sythese_haar(jpeg2000::Signal1D::LELECCUM(), "test_haar", true);
    }

    void leleccum_analyse_synthese_haar() {
        _analyse_sythese_haar(jpeg2000::Signal1D::LELECCUM(), "test_haar", false);
    }

    void rampe_analyse_synthese_haar97() {
        _analyse_sythese_haar(jpeg2000::Signal1D::RAMPE(), "test_haar", true);
    }

    void rampe_analyse_synthese_haar() {
        _analyse_sythese_haar(jpeg2000::Signal1D::RAMPE(), "test_haar" ,false);
    }

    void rampe_analyse_synthese_lifting97(){
        _analyse_synthese_lifting97(jpeg2000::Signal1D::RAMPE(), "test_lifting");
    }

    void leleccum_analyse_synthese_lifting97(){
        _analyse_synthese_lifting97(jpeg2000::Signal1D::LELECCUM(), "test_lifting");
    }

    void _analyse_synthese_lifting97(const Signal1D& in, const std::string& folderOut) {
        _analyse_synthese(in, folderOut, false, true);
    }

    void lena_haar_haar97_lifting97(){
        const std::string lenaMiddleFile = jpeg2000::assets::paths::LENA_FILE;
        Signal1D lenaMiddleLine = (Signal1D::readFromFile(lenaMiddleFile));
        lenaMiddleLine.setName("LenaMiddleLine");

        _analyse_sythese_haar(lenaMiddleLine, "test_lena/haar", false);
        _analyse_sythese_haar(lenaMiddleLine, "test_lena/haar97", true);
        _analyse_synthese_lifting97(lenaMiddleLine, "test_lena/lifting97");
    }
}
}



