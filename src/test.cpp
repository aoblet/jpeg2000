#include "test.hpp"
#include "decompose.hpp"
#include "decomposeHaar.hpp"
#include "decomposeLifting.hpp"
#include "decomposeAMR.hpp"
#include "decompose2D.hpp"
#include "assets.hpp"
#include "statistics.hpp"

#include <fstream>
#include <algorithm>
#include <assets.hpp>
#include <boost/filesystem/path.hpp>
#include "bitmap.hpp"


namespace jpeg2000{ namespace test{
    void _analyse_synthese(const jpeg2000::Signal1D &in, const std::string &folderOut, bool isHaar, bool is97,
                           bool isAMR, int levelAMR){
        std::string folderTestsOut = "tests/" + folderOut;
        std::string command_mkdir("mkdir -p " + folderTestsOut);
        std::string baseOutPath(folderTestsOut + "/" + in.name() + "_");
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
        else if(isAMR){
            analyse = decompose::AMR::computeAMR(in, levelAMR);
            synth = decompose::AMR::computeIAMR(analyse, levelAMR);
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
        _analyse_sythese_haar(Signal1D::LENA(), "test_lena/haar", false);
        _analyse_sythese_haar(Signal1D::LENA(), "test_lena/haar97", true);
        _analyse_synthese_lifting97(Signal1D::LENA(), "test_lena/lifting97");
    }

    void lena_analyse_synthese_AMR(){
//        _analyse_synthese_AMR(Signal1D::LENA(), "test_lena/AMR/1", 1);
        _analyse_synthese_AMR(Signal1D::LENA(), "test_lena/AMR/2", 2);
//        _analyse_synthese_AMR(Signal1D::LENA(), "test_lena/AMR/3", 3);
//        _analyse_synthese_AMR(Signal1D::LENA(), "test_lena/AMR/4", 4);
//        _analyse_synthese_AMR(Signal1D::LENA(), "test_lena/AMR/5", 5);
//        _analyse_synthese_AMR(Signal1D::LENA(), "test_lena/AMR/6", 6);
//        _analyse_synthese_AMR(Signal1D::LENA(), "test_lena/AMR/7", 7);
//        _analyse_synthese_AMR(Signal1D::LENA(), "test_lena/AMR/8", 8);
//        _analyse_synthese_AMR(Signal1D::LENA(), "test_lena/AMR/9", 9);
    }
    void _analyse_synthese_AMR(const Signal1D& in, const std::string& folderOut, int levelAMR){
        _analyse_synthese(in, folderOut, false, false, true, levelAMR);
    }

    void lena_AMR_statistics(int level){
        Signal1D amrAnalyse = jpeg2000::decompose::AMR::computeAMR(Signal1D::LENA(), level);
        std::cout << "LENA statistics" << std::endl;

        std::cout << "LENA original max " << Signal1D::LENA().max() << std::endl;
        std::cout << "LENA original min " << Signal1D::LENA().min() << std::endl;
        std::cout << "LENA original mean " << Signal1D::LENA().mean() << std::endl;

        std::cout << "LENA AMR max " << amrAnalyse.max() << std::endl;
        std::cout << "LENA AMR min " << amrAnalyse.min() << std::endl;
        std::cout << "LENA AMR mean " << amrAnalyse.mean() << std::endl;
    }

    void _lena2D(bool isHaar, int levelAMR){
        const std::string folderOut = "tests/bmp/";
        const std::string commandMkdir = "mkdir -p " + folderOut;
        system(commandMkdir.c_str());
        Signal2D mat(bmp::loadBMP_256(assets::paths::LENA_BMP));

        if(isHaar)
            bmp::writeBMP_256(folderOut + "lenaHaar.bmp", decompose::_2D::analyse2D_97(mat));
        else{
            Signal2D analyse(decompose::_2D::amr(mat, levelAMR));
            Signal2D synth(decompose::_2D::iamr(analyse, levelAMR));

            bmp::writeBMP_256(folderOut + "lenaAMR_analyse2.bmp", analyse);
            bmp::writeBMP_256(folderOut + "lenaAMR_synth2.bmp", synth);
            std::cout << "MSE AMR level " << levelAMR << std::endl;
            std::cout << decompose::_2D::quadraticError(mat, synth);
        }

    }
    void lena2D_haar(){
        _lena2D(true);
    }

    void lena2D_AMR(){
        _lena2D(false, 3);
    }

    void statsMeanVariance2D(){
        const std::string folderOut = "tests/bmp/";
        const std::string commandMkdir = "mkdir -p " + folderOut;
        system(commandMkdir.c_str());

        int levelAMR = 3;
        Signal2D s = decompose::_2D::amr(bmp::loadBMP_256(assets::paths::LENA_BMP), levelAMR);

        std::vector<ResultStat> res;
        statistics::computeMeanVarianceSubbands2D(s, levelAMR, res);
        for(auto& r: res){
            std::cout << r << std::endl;
        }
    }

    void statsDebit(){
        const std::string folderOut = "tests/debit/";
        const std::string commandMkdir = "mkdir -p " + folderOut;
        system(commandMkdir.c_str());

        int levelAMR = 3;
        Signal2D s = decompose::_2D::amr(bmp::loadBMP_256(assets::paths::LENA_BMP), levelAMR);

        std::vector<ResultStat> res;
        float debitGlobal = 1;
        statistics::computeDebitSubbands(s, levelAMR, debitGlobal, res);
        for(auto& r: res){
            std::cout << r.debit << std::endl;
        }
        std::cout << res.size() ;
    }

    void quantify(){
        int levelAMR = 3;
        const std::string folderOut = "tests/quantlm/";
        const std::string commandMkdir = "mkdir -p " + folderOut;
        system(commandMkdir.c_str());
        Signal2D s = decompose::_2D::amr(bmp::loadBMP_256(assets::paths::LENA_BMP), levelAMR);

        std::vector<ResultStat> res;
        float debitGlobal = 1;

        statistics::computeQuantlmSubbands(s, levelAMR, debitGlobal, res);
        bmp::writeBMP_256(folderOut + "lenaAMR_analyse3.bmp", decompose::_2D::iamr(s, levelAMR));
    }

    void peakSignalNoiseRatio(float debitGlobal){
        int levelAMR = 3;
        const std::string folderOut = "tests/psnr/";
        const std::string commandMkdir = "mkdir -p " + folderOut;
        system(commandMkdir.c_str());
        Signal2D original(bmp::loadBMP_256(assets::paths::LENA_BMP));
        Signal2D s = decompose::_2D::amr(original, levelAMR);

        std::vector<ResultStat> res;
        statistics::computeQuantlmSubbands(s, levelAMR, debitGlobal, res);
        Signal2D synth(decompose::_2D::iamr(s, levelAMR));

//        std::cout << " PSNR " << std::endl;
//        std::cout << " Level AMR " << levelAMR << std::endl;
//        std::cout << " Debit global " << debitGlobal << std::endl;
//        std::cout << " PSNR " << decompose::_2D::peakSignalNoiseRatio(synth, original) << std::endl;
        std::cout << decompose::_2D::peakSignalNoiseRatio(synth, original) << std::endl;
        bmp::writeBMP_256(folderOut + "leanAMR_psnr.bmp", synth);
    }

    void compressQuantlmIdx(float debit){
        int levelAMR = 3;
        const std::string folderOut = "tests/compress/";
        const std::string commandMkdir = "mkdir -p " + folderOut;
        system(commandMkdir.c_str());
        Signal2D s = decompose::_2D::amr(bmp::loadBMP_256(assets::paths::LENA_BMP), levelAMR);

        std::vector<ResultStat> res;

        statistics::computeQuantlmSubbands(s, levelAMR, debit, res, true);

        std::fstream compress(folderOut + "lena_" + std::to_string(debit) + ".bin", std::ios::out);
        for(int y = 0; y< s.rows(); ++y) {
            for (int x = 0; x < s.cols(); ++x) {
                compress.write((char*)&s[y][x], sizeof(double));
            }
        }

        bmp::writeBMP_256(folderOut + "lena " + std::to_string(debit) + ".bmp", decompose::_2D::iamr(s, levelAMR));
    }

}
}