#pragma once

#include "Signal2D.hpp"
#include <vector>
#include <cmath>

typedef struct Vec2{
    int x;
    int y;
    Vec2(int _x, int _y): x(_x), y(_y){}
    void set(int _x, int _y){x = _x; y = _y;}
} Vec2;


typedef struct ResultatStat{
    double mean;
    double variance;
    double debit;
    std::string subband;
    int levelAMR;
    int nbPixelsSubband;

    ResultatStat(double _mean, double _variance, int _levelAMR, const std::string& _subband, double _debit=-1, int _nbPixelsSubband=0)
            :mean(_mean), variance(_variance), levelAMR(_levelAMR), subband(_subband), debit(_debit), nbPixelsSubband(_nbPixelsSubband){}

} ResultStat;

inline std::ostream& operator<<(std::ostream& out, const ResultStat& stat){
    std::cout << "LevelAMR: " << stat.levelAMR << std::endl;
    std::cout << "Subband: "  << stat.subband  << std::endl;
    std::cout << "Mean: "     << stat.mean     << std::endl;
    std::cout << "Variance: " << stat.variance << std::endl;
    std::cout << "Debit: "    << stat.debit<< std::endl;
    return out;
};

namespace jpeg2000{
namespace statistics{
    // amr level l*3 + 1 => subbands
    double meanSubband2D(const Signal2D& mat, const Vec2& from, const Vec2& to);
    double varianceSubband2D(const Signal2D& mat, const Vec2& from, const Vec2& to);
    void computeMeanVarianceSubbands2D(const Signal2D& mat, int levelAMR, std::vector<ResultStat>& results);
    void computeDebitSubbands(const Signal2D& mat, int levelAMR, float globalDebit, std::vector<ResultStat>& results);
    void computeQuantlmSubbands(Signal2D& mat, int levelAMR, float globalDebit, std::vector<ResultStat>& results, bool isIdx=false);
}
}