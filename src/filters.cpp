#include <cmath>
#include "filters.hpp"

namespace jpeg2000{
    namespace filters{
        Signal1D interpole2(const Signal1D& signal){
            Signal1D interpolated;
            for(double x: signal){
                interpolated.push_back(x);
                interpolated.push_back(0);
            }
            return interpolated;
        }

        Signal1D decimation2(const Signal1D& signal){
            Signal1D decimated;
            int halfSize = (int)signal.size()/2;

            for(int i=0; i<halfSize; ++i)
                decimated.push_back(signal[i<<1]); // <<1 == *2
            return decimated;
        }
        Signal1D convol(const Signal1D& signal, const Signal1D& filter){
            int sizeSignal = (int)signal.size(),
                    sizeFilter = (int)filter.size();
            Signal1D filtered(sizeSignal, 0);

            for(int n=0; n<sizeSignal; ++n){
                for(int k=-sizeFilter/2; k<sizeFilter/2; ++k){
                    // handle mirror symmetry
                    filtered[n] += filter[k + (sizeFilter/2)]*mirrorSymmetry(signal, n-k);
                }
            }
            return filtered;
        }

        double mirrorSymmetry(const Signal1D& signal, const int i){
            if(i < -1)
                return signal[i*-1];
            if(i> signal.size()-1)
                return signal[2*signal.size() - i + 1];
            return signal[i];
        }

        Signal1D analyseHaar(const Signal1D& signal){
            // sld == signalLowPassDecimated
            // shd == signalHighPassDecimated
            Signal1D  sld, shd, concat_sld_shd,
                    _h0 {1.0/sqrt(2), 1.0/sqrt(2) , 0},
                    _h1 {1.0/sqrt(2), -1.0/sqrt(2), 0};

            sld = decimation2(convol(signal, _h0));
            shd = decimation2(convol(signal, _h1));
            concat_sld_shd = sld;
            concat_sld_shd.insert(concat_sld_shd.end(), shd.begin(), shd.end());

            return concat_sld_shd;
        }
    }
}
