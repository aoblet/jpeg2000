//
// Created by alex on 22/10/15.
//

#include "Signal1D.hpp"
#include <sstream>
#include <boost/filesystem.hpp>
#include <fstream>

namespace jpeg2000{
    Signal1D Signal1D::_RAMPE("rampe");
    Signal1D Signal1D::_LELECCUM("leleccum");

    Signal1D::Signal1D():_val(), _name("1D Signal"){};

    Signal1D::Signal1D(const std::string & name, int n, double initVal):
            _val(std::vector<double>::size_type(n), initVal),
            _name(name){};

    Signal1D::Signal1D(const std::string& name): Signal1D(name, 0, 0){}
    Signal1D::Signal1D(int n, double initVal): Signal1D("1D Signal", n, initVal){}
    Signal1D::Signal1D(int n) : Signal1D(n, 0){}
    Signal1D::Signal1D(const Signal1D& s):_val(s._val), _name(s._name){};
    Signal1D::Signal1D(std::initializer_list<double> __l    ): _val(__l), _name("1D Signal"){}

    Signal1D::Signal1D(Signal1D&& s) noexcept :_val(std::move(s._val)), _name(std::move(s._name)){};

    Signal1D& Signal1D::operator=(Signal1D&& other) noexcept {
        std::swap(_val, other._val);
        std::swap(_name, other._name);
        return *this;
    }

    std::string Signal1D::name() const{
        return _name;
    }

    void Signal1D::setName(const std::string& name) {
        _name = name;
    }

    Signal1D& Signal1D::operator=(const Signal1D& other){
        _val = other._val;
        _name = other._name;
        return *this;
    }

    int Signal1D::size() const{
        return (int)_val.size();
    }

    void Signal1D::push_back(double v){
        _val.push_back(v);
    }

    double Signal1D::operator[](int i) const{
        return _val[i];
    }

    double& Signal1D::operator[](int i){
        return _val[i];
    }

    std::vector<double>::iterator Signal1D::begin(){
        return _val.begin();
    }

    std::vector<double>::const_iterator Signal1D::begin() const{
        return _val.begin();
    }

    std::vector<double>::iterator Signal1D::end(){
        return _val.end();
    }

    std::vector<double>::const_iterator Signal1D::end() const{
        return _val.end();
    }

    Signal1D& operator+=(Signal1D& s1, const Signal1D& s2){
        int n = std::min(s1.size(), s2.size());
        for(int i=0; i<n; ++i)
            s1[i] += s2[i];
        return s1;
    }

    Signal1D operator+(const Signal1D& s1, const Signal1D& s2){
        Signal1D tmp(s1);
        return tmp += s2;
    }

    std::ostream& operator<<(std::ostream &out, const Signal1D &signal) {
        out << "# Representation of: " << signal._name << std::endl;
        for(auto tt: signal)
            out << tt << std::endl;
        return out;
    }

    const Signal1D& Signal1D::rampe() {
        if(Signal1D::_RAMPE.size())
            return Signal1D::_RAMPE;
        for(int i=0; i<256; ++i)
            Signal1D::_RAMPE.push_back(i);
        return Signal1D::_RAMPE;
    }

    const Signal1D& Signal1D::leleccum() {
        if(Signal1D::_LELECCUM.size())
            return Signal1D::_LELECCUM;

        std::ifstream in(boost::filesystem::path(__FILE__ ).parent_path().string() + "/../assets/leleccum.txt");
        std::string l;
        std::stringstream cast;
        double t;

        while(getline(in, l)){
            cast.clear();
            cast << l;

            if(cast>>t)
                Signal1D::_LELECCUM.push_back(t);
        }
        return Signal1D::_LELECCUM;
    }

    Signal1D& Signal1D::operator+=(const double n){
        push_back(n);
        return *this;
    }

    Signal1D Signal1D::concat(const Signal1D& other) const{
        Signal1D tmp(*this);
        tmp._val.insert(tmp._val.end(), other._val.begin(), other._val.end());
        return tmp;
    }

    Signal1D Signal1D::extract(int f, int t) const{
        assert(f>-1 && t<size());
        Signal1D tmp;

        // like python style with index == -1
        if(t < 0)
            t = size() - 1;
        for(int i=f; i <= t; ++i)
            tmp.push_back((*this)[i]);
        return tmp;
    }

}
