//
// Created by alex on 21/10/15.
//

#ifndef JPEG2000_FILTER_H
#define JPEG2000_FILTER_H

#include <vector>

namespace jpeg2000 {
    namespace filters {
        using namespace std;

        vector<double> interpole2(const vector<double>& signal);
        vector<double> decimation2(const vector<double>& signal);
        vector<double> convol(const vector<double>& signal, const vector<double>& filter);
        vector<double> analyseHaar(const vector<double>& signal);
    }
}
#endif //JPEG2000_FILTER_H
