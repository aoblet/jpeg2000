#include "decompose2D.hpp"
#include "decomposeAMR.hpp"
#include "decomposeLifting.hpp"
#include "decomposeHaar.hpp"
#include <iostream>
#include "bitmap.hpp"
#include <stdexcept>
#include <cmath>
#include <assert.h>

namespace jpeg2000{
namespace decompose{
namespace _2D{

    Signal2D analyse2D_97(const Signal2D& s){
        // decompose all the lines then the all cols (lines decomposed encapsulated)
        Signal2D bmpMatrix(s), analysedLines;

        // decompose on analysedLines
        for(int i=0; i<bmpMatrix.rows(); ++i)
            analysedLines.push_back(std::move(decompose::haar::analyseHaar97(bmpMatrix[i])));

        // decompose on cols
        // reuse bmpMatrix as result
        for(int i=0; i< analysedLines.cols(); ++i)
            bmpMatrix.eraseCol(i, std::move(decompose::haar::analyseHaar97(analysedLines.col(i))));

        return bmpMatrix;
    }
    Signal2D amr(const Signal2D& s, int level){

        Signal2D bmpMatrix(s);
        int widthAppro = s.cols(), heightAppro = s.rows();
        int maxLevelRows = decompose::AMR::maxLevelFromNumber(s.rows()),
            maxLevelCols = decompose::AMR::maxLevelFromNumber(s.cols());

        if(level > maxLevelCols || level > maxLevelRows)
            throw std::runtime_error(std::string("The level " + std::to_string(level) + " is too high").c_str());

        Signal2D iamrCols;

        for(int l=1; l<=level; ++l){
            Signal2D tmp = bmpMatrix.extract(widthAppro, heightAppro);
            iamrCols.resize((size_t)tmp.rows());

            for(int i=0; i<tmp.rows(); ++i)
                iamrCols[i] = std::move(decompose::AMR::computeAMR(tmp[i], 1));
            for(int i=0; i< iamrCols.cols(); ++i)
                bmpMatrix.eraseCol(i, std::move(decompose::AMR::computeAMR(iamrCols.col(i), 1)));

            widthAppro /= 2;
            heightAppro /= 2;
        }

        // update dynamic range
//
//        double min = bmpMatrix[0][0], max = bmpMatrix[0][0];
//        double v;
//        for(int y=0; y<heightAppro; ++y){
//            for(int x=0; x<widthAppro; ++x){
//                v = bmpMatrix[y][x];
//                if(v < min)
//                    min = v;
//                if(v > max)
//                    max = v;
//            }
//        }
//
//        double minPlusMax = max - min;
//        for(int y=0; y<heightAppro; ++y){
//            for(int x=0; x<widthAppro; ++x) {
//                v = bmpMatrix[y][x];
//                bmpMatrix[y][x] = (v - min)/(minPlusMax) * 255;
//            }
//        }
//
//        for(int y=0; y<bmpMatrix.rows(); ++y){
//            for(int x=0; x<bmpMatrix.cols(); ++x) {
//                if(y < heightAppro && x < widthAppro)
//                    continue;
//                if((int) bmpMatrix[y][x] > 10)
//                    bmpMatrix[y][x] += 127;
//            }
//        }
        return bmpMatrix;
    }

    Signal2D iamr(const Signal2D& s, int level) {

        Signal2D bmpMatrix(s);
        int amrWidth = s.cols()/(std::pow(2,level-1)),
            amrHeight = s.rows()/(std::pow(2,level-1));
//        int amrWidth = s.cols(),
//            amrHeight = s.rows();

        Signal2D amrMatrix;
        Signal2D iamrCols;

        std::cout << amrWidth << std::endl;
        std::cout << amrHeight << std::endl;

        for (int l = 1; l <= level; ++l) {
            amrMatrix = bmpMatrix.extract(amrWidth, amrHeight);
            iamrCols.resize((size_t) amrMatrix.cols());

            // the iamrCols[i] contains the imar signal of column i (transposed)
            for (int i = 0; i < amrMatrix.cols(); ++i)
                iamrCols[i] = std::move(decompose::AMR::computeIAMR(amrMatrix.col(i), 1));

            // once the iamr columns is done, we need to compute the iamr of the lines
            // now let's compute the imar of the col(i) as we stored the previous results as transposed
            for (int i = 0; i < iamrCols.rows(); ++i)
                bmpMatrix.eraseRow(i, std::move(decompose::AMR::computeIAMR(iamrCols.col(i), 1)));

            amrWidth *= 2;
            amrHeight *= 2;

        }
        return bmpMatrix;
    }
    double quadraticError(const Signal2D &s1, const Signal2D &s2){
        assert(s1.cols() == s2.cols() && s1.rows() == s2.rows());
        double error = 0;

        for(int y = 0; y< s1.rows(); ++y) {
            for (int x = 0; x < s1.cols(); ++x) {
                error += std::pow(s1[y][x] - s2[y][x], 2);
            }
        }
        return error;
    }

    double peakSignalNoiseRatio(const Signal2D &s1, const Signal2D &s2) {
        assert(s1.cols() == s2.cols() && s1.rows() == s2.rows());
        double mse = quadraticError(s1, s2)  / (s1.rows() * s1.cols());
        std::cout << " MSE " <<  mse << std::endl;
        return 10 * std::log10(std::pow(255,2) / mse);
    }
}
}
}