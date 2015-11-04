#include "filters.hpp"
#include <cmath>

jpeg2000::Signal1D buildHaarFilter_analyse97(bool isLow){
    jpeg2000::Signal1D res;

    if(isLow){
        // biorthogonal filter 9/7 _h0 (length 9): Low filter
        res.push_back(0.037828455507  );
        res.push_back(-0.023849465019 );
        res.push_back(-0.110624404418 );
        res.push_back(0.377402855613  );
        res.push_back(0.852698679009  );
        res.push_back(0.377402855613  );
        res.push_back(-0.110624404418 );
        res.push_back(-0.023849465019 );
        res.push_back(0.037828455507  );
        return res;
    }

    // biorthogonal filter 9/7 _h1 (length 9): High filter
    res.push_back(0.064538882629 );
    res.push_back(-0.040689417610);
    res.push_back(-0.418092273222);
    res.push_back(0.788485616406 );
    res.push_back(-0.418092273222);
    res.push_back(-0.040689417610);
    res.push_back(0.064538882629 );
    res.push_back(0.000000000000 );
    res.push_back(-0.000000000000);

    return res;
}

jpeg2000::Signal1D buildHaarFilter_synthesis97(bool isLow){
    jpeg2000::Signal1D res;

    if(isLow){
        // biorthogonal filter 9/7 _g0 (length 7)
        res.push_back(-0.064538882629);
        res.push_back(-0.040689417610);
        res.push_back(0.418092273222 );
        res.push_back(0.788485616406 );
        res.push_back(0.418092273222 );
        res.push_back(-0.040689417610);
        res.push_back(-0.064538882629);
        return res;
    }
    // biorthogonal filter 9/7 _g1 (length 11)
    res.push_back(0.000000000000 );
    res.push_back(-0.000000000000);
    res.push_back(0.037828455507 );
    res.push_back(0.023849465019 );
    res.push_back(-0.110624404418);
    res.push_back(-0.377402855613);
    res.push_back(0.852698679009 );
    res.push_back(-0.377402855613);
    res.push_back(-0.110624404418);
    res.push_back(0.023849465019 );
    res.push_back(0.037828455507 );
    return res;
}

namespace jpeg2000{
namespace filters{
    const Signal1D ANALYSE_LOW_HAAR{1.0 / sqrt(2), 1.0 / sqrt(2), 0};
    const Signal1D ANALYSE_HIGH_HAAR{1.0 / sqrt(2), -1.0 / sqrt(2), 0};
    const Signal1D SYNTHESIS_LOW_HAAR{0, 1.0 / sqrt(2), 1.0 / sqrt(2)};
    const Signal1D SYNTHESIS_HIGH_HAAR{0, -1.0 / sqrt(2), 1.0 / sqrt(2)};

    const Signal1D ANALYSE_LOW_HAAR_97(std::move(buildHaarFilter_analyse97(true)));
    const Signal1D ANALYSE_HIGH_HAAR_97(std::move(buildHaarFilter_analyse97(false)));
    const Signal1D SYNTHESIS_LOW_HAAR_97(std::move(buildHaarFilter_synthesis97(true)));
    const Signal1D SYNTHESIS_HIGH_HAAR_97(std::move(buildHaarFilter_synthesis97(false)));
}}
