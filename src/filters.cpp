#include <cmath>
#include "filters.hpp"

namespace jpeg2000{
    namespace filters{
        vector<double> interpole2(const vector<double>& signal){
            vector<double> interpolated;
            for(double x: signal){
                interpolated.push_back(x);
                interpolated.push_back(0);
            }
            return interpolated;
        }

        vector<double> decimation2(const vector<double>& signal){
            vector<double> decimated;
            int halfSize = (int)signal.size()/2;

            for(int i=0; i<halfSize; ++i)
                decimated.push_back(signal[i<<1]); // <<1 == *2
            return decimated;
        }

        vector<double> convol(const vector<double>& signal, vector<double>& filter){
            int sizeSignal = (int)signal.size(),
                    sizeFilter = (int)filter.size();
            vector<double> filtered((size_t)sizeSignal, 0);

            double tmpSignal_n_minus_k;
            for(int n=0; n<sizeSignal; ++n){
                for(int k=-sizeFilter/2; k<sizeFilter/2; ++k){
                    // handle mirror symmetry
                    if(n-k < -1)
                        tmpSignal_n_minus_k = signal[(n-k) * -1];
                    else if(n-k > sizeSignal -1)
                        tmpSignal_n_minus_k = signal[2*sizeSignal - ((n-k) - sizeSignal+1)];
                    else
                        tmpSignal_n_minus_k = signal[n-k];

                    filtered[n] += filter[k + (sizeFilter/2)]*tmpSignal_n_minus_k;
                }
            }
            return filtered;
        }

        vector<double> analyseHaar(const vector<double>& signal){
            vector<double>  xb, xh, concat_xb_xh,
                    _h0 {1.0/sqrt(2), 1.0/sqrt(2) , 0},
                    _h1 {1.0/sqrt(2), -1.0/sqrt(2), 0};

            xb = decimation2(convol(signal, _h0));
            xh = decimation2(convol(signal, _h1));
            concat_xb_xh = xb;
            concat_xb_xh.insert(concat_xb_xh.end(), xh.begin(), xh.end());

            return concat_xb_xh;
        }
    }
}
