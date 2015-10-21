//
// Created by alex on 22/10/15.
//

#ifndef JPEG2000_SIGNAL1D_HPP
#define JPEG2000_SIGNAL1D_HPP

#include <vector>

namespace jpeg2000{
    class Signal1D: public std::vector<double>{
    public:
        Signal1D();
        Signal1D(int n);
        Signal1D(int n, double initVal);
        Signal1D(const Signal1D& s);
        Signal1D(Signal1D&& s);
        Signal1D(std::initializer_list<double> __l);
        Signal1D& operator=(const Signal1D& s);
    };
}

#endif //JPEG2000_SIGNAL_HPP
