//
// Created by alex on 22/10/15.
//

#include "Signal1D.hpp"
namespace jpeg2000{
    Signal1D::Signal1D():vector(){};
    Signal1D::Signal1D(int n, double initVal): vector(size_type(n%2 ? n+1 : n), initVal){}
    Signal1D::Signal1D(int n) : Signal1D(n, 0){}
    Signal1D::Signal1D(const Signal1D& s):vector(s){};
    Signal1D::Signal1D(Signal1D&& s):vector(s){};
    Signal1D::Signal1D(std::initializer_list<double> __l): vector(__l){
        if(size()%2)
            push_back(0);
    }
    Signal1D& Signal1D::operator=(const Signal1D& s){
        std::vector<double>::operator=((std::vector<double>)s);
        return *this;
    }
}