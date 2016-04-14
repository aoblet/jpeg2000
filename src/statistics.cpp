#include "statistics.hpp"
#include <cassert>
#include <cmath>
#include "quantlm.hpp"

namespace jpeg2000{
namespace statistics{

    double meanSubband2D(const Signal2D& mat, const Vec2& from, const Vec2& to){
        assert(from.x >= 0 && from.x <= mat.cols() && from.y >= 0 && from.y <= mat.rows());
        assert(to.x >= 0 && to.x <= mat.cols() && to.y >= 0 && to.y <= mat.rows());

        double res(0);
        for(int x = from.x; x< to.x; ++x){
            for(int y=from.y; y<to.y; ++y){
                res += mat[y][x];
            }
        }
        return res / ((to.x - from.x) * (to.y - from.y));
    }

    double varianceSubband2D(const Signal2D& mat, const Vec2& from, const Vec2& to){
        double mean(meanSubband2D(mat, from, to));
        double res(0);

        for(int x = from.x; x< to.x; ++x) {
            for (int y = from.y; y < to.y; ++y) {
                res += std::pow(mat[y][x] - mean, 2);
            }
        }
        return res / ((to.x - from.x) * (to.y - from.y));
    }

    void computeMeanVarianceSubbands2D(const Signal2D& mat, int levelAMR, std::vector<ResultStat>& results){

        Vec2 subbandFrom(0,0), subbandTo(0,0);
        int width = mat.cols(), height = mat.rows();
        double mean, variance;
        std::string nameSubband;

        for(int l=1; l <= levelAMR; ++l) {
            mean = 0;
            variance = 0;
            width /= 2;
            height /= 2;

            for (int regionSubband = 0; regionSubband < 4; ++regionSubband) {
                //topRight
                if (regionSubband == 0) {
                    subbandFrom =Vec2(width, 0);
                    subbandTo = Vec2(width*2, height);
                    nameSubband = "TopRight";
                }
                //bottomLeft
                else if (regionSubband == 1) {
                    subbandFrom = Vec2(0, height);
                    subbandTo = Vec2(width, height * 2);
                    nameSubband = "BottomLeft";
                }
                //bottomRight
                else if (regionSubband == 2){
                    subbandFrom = Vec2(width, height);
                    subbandTo = Vec2(width * 2, height * 2);
                    nameSubband = "BottomRight";
                }
                //topLeft
                else if(regionSubband == 3 && l == levelAMR){
                    subbandFrom = Vec2(0, 0);
                    subbandTo = Vec2(width, height);
                    nameSubband = "TopLeft";
                }

                if(l != levelAMR && regionSubband == 3)
                    continue;

                Vec2 tmpRealNbPixel(subbandTo.x - subbandFrom.x, subbandTo.y - subbandFrom.y);
                int nbPixelsSubband = tmpRealNbPixel.x * tmpRealNbPixel.y;

                mean = meanSubband2D(mat, subbandFrom, subbandTo);
                variance = varianceSubband2D(mat, subbandFrom, subbandTo);
                results.push_back(ResultatStat(mean, variance, l, nameSubband, -1, nbPixelsSubband));
            }
        }
    }



    void computeDebitSubbands(const Signal2D& mat, int levelAMR, float globalDebit, std::vector<ResultStat>& results){
        Vec2 subbandFrom(0,0), subbandTo(0,0);
        int width = mat.cols(), height = mat.rows();
        int nbPixels = width * height;
        double mean, variance;
        std::string nameSubband;
        double debit;
        double customVariance = 1;

        std::vector<ResultStat> variances;
        float sizeTotal = 0;
        computeMeanVarianceSubbands2D(mat, levelAMR, variances);

        for(ResultStat& r : variances)
            customVariance *= std::pow(r.variance, double(r.nbPixelsSubband)/nbPixels);

        double moyenne = 0;

        for(int l=1; l <= levelAMR; ++l) {
            mean = 0;
            variance = 0;
            width /= 2;
            height /= 2;

            int tmpNbPixels = mat.cols() / (std::pow(2, l)) * mat.rows() / (std::pow(2, l));

            for (int regionSubband = 0; regionSubband < 4; ++regionSubband) {
                //topRight
                if (regionSubband == 0) {
                    subbandFrom = Vec2(width, 0);
                    subbandTo = Vec2(width*2, height);
                    nameSubband = "TopRight";
                }
                    //bottomLeft
                else if (regionSubband == 1) {
                    subbandFrom = Vec2(0, height);
                    subbandTo = Vec2(width, height * 2);
                    nameSubband = "BottomLeft";
                }
                    //bottomRight
                else if (regionSubband == 2){
                    subbandFrom = Vec2(width, height);
                    subbandTo = Vec2(width * 2, height * 2);
                    nameSubband = "BottomRight";
                }
                    //topLeft
                else if(regionSubband == 3 && l == levelAMR){
                    subbandFrom = Vec2(0, 0);
                    subbandTo = Vec2(width, height);
                    nameSubband = "TopLeft";
                }


                if(l != levelAMR && regionSubband == 3)
                    continue;

                mean = meanSubband2D(mat, subbandFrom, subbandTo);
                variance = varianceSubband2D(mat, subbandFrom, subbandTo);
                Vec2 tmpRealNbPixel(subbandTo.x - subbandFrom.x, subbandTo.y - subbandFrom.y);
                debit = globalDebit + (0.5 * std::log2(variance/customVariance));
                results.push_back(ResultatStat(mean, variance, l, nameSubband, debit));
                sizeTotal += (debit * tmpRealNbPixel.x * tmpRealNbPixel.y)/ 8000.0;
            }

        }
        std::cout << "sizeTotal " << sizeTotal  << std::endl;
    }

    void computeQuantlmSubbands(Signal2D& mat, int levelAMR, float globalDebit, std::vector<ResultStat>& results, bool isIdx){
        Vec2 subbandFrom(0,0), subbandTo(0,0);
        int width = mat.cols(), height = mat.rows();
        int nbPixels = width * height;
        double mean, variance;
        std::string nameSubband;
        double debit;
        double customVariance = 1;

        std::vector<ResultStat> variances;
        float sizeTotal = 0;
        computeMeanVarianceSubbands2D(mat, levelAMR, variances);
        for(ResultStat& r : variances)
            customVariance *= std::pow(r.variance, double(r.nbPixelsSubband)/nbPixels);

        double moyenne = 0;

        for(int l=1; l <= levelAMR; ++l) {
            mean = 0;
            variance = 0;
            width /= 2;
            height /= 2;

            int tmpNbPixels = mat.cols() / (std::pow(2, l)) * mat.rows() / (std::pow(2, l));

            for (int regionSubband = 0; regionSubband < 4; ++regionSubband) {
                //topRight
                if (regionSubband == 0) {
                    subbandFrom = Vec2(width, 0);
                    subbandTo = Vec2(width*2, height);
                    nameSubband = "TopRight";
                }
                    //bottomLeft
                else if (regionSubband == 1) {
                    subbandFrom = Vec2(0, height);
                    subbandTo = Vec2(width, height * 2);
                    nameSubband = "BottomLeft";
                }
                    //bottomRight
                else if (regionSubband == 2){
                    subbandFrom = Vec2(width, height);
                    subbandTo = Vec2(width * 2, height * 2);
                    nameSubband = "BottomRight";
                }
                    //topLeft
                else if(regionSubband == 3 && l == levelAMR){
                    subbandFrom = Vec2(0, 0);
                    subbandTo = Vec2(width, height);
                    nameSubband = "TopLeft";
                }


                if(l != levelAMR && regionSubband == 3)
                    continue;

                mean = meanSubband2D(mat, subbandFrom, subbandTo);
                variance = varianceSubband2D(mat, subbandFrom, subbandTo);
                Vec2 tmpRealNbPixel(subbandTo.x - subbandFrom.x, subbandTo.y - subbandFrom.y);
                debit = globalDebit + (0.5 * std::log2(variance/customVariance));
//                std::cout << std::pow(2,debit) << " " << nameSubband  << std::endl;
                results.push_back(ResultatStat(mean, variance, l, nameSubband, debit));
                sizeTotal += (debit * tmpRealNbPixel.x * tmpRealNbPixel.y)/ 8000.0;


                std::vector<double> subbandAs1D;
                for(int y=subbandFrom.y; y<subbandTo.y; ++y){
                    for(int x = subbandFrom.x; x< subbandTo.x; ++x){
                        subbandAs1D.push_back(mat[y][x]);
                    }
                }

                quantlm(subbandAs1D.data(), subbandAs1D.size(),  std::pow(2, debit) , isIdx);

                int widthSubband = subbandTo.x - subbandFrom.x;
                int cpt = 0;
                for(int y=subbandFrom.y; y<subbandTo.y; ++y){
                    for(int x = subbandFrom.x; x< subbandTo.x; ++x){
                        mat[y][x] = subbandAs1D[cpt] ;
//                        std::cout << subbandAs1D[cpt] << std::endl;
                        ++cpt;
                    }
                }
            }
//            std::cout << nameSubband << std::endl;
//            std::getchar();
//            std::system("clear");
        }
        std::cout << sizeTotal << std::endl;
    }

}
}