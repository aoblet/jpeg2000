//
// Created by alex on 22/10/15.
//

#include "Signal1D.hpp"
#include <sstream>
#include <fstream>
#include <boost/filesystem.hpp>


namespace jpeg2000{
    Signal1D Signal1D::_RAMPE;
    Signal1D Signal1D::_LELECCUM;

    Signal1D::Signal1D():_val(), _name("1D Signal"){};
    Signal1D::Signal1D(const std::string & name, int n, double initVal, bool isPair): _val(std::vector<double>::size_type(isPair && n%2 ? n+1 : n), initVal),
                                                                         _name(name), _isPair(isPair){};
    Signal1D::Signal1D(int n, double initVal): Signal1D("1D Signal", n, initVal){}
    Signal1D::Signal1D(int n) : Signal1D(n, 0){}
    Signal1D::Signal1D(const Signal1D& s):_val(s._val), _name(s._name), _isPair(s._isPair){};
    Signal1D::Signal1D(std::initializer_list<double> __l    ): _val(__l), _name("1D Signal"){}

    Signal1D::Signal1D(Signal1D&& s) noexcept :_val(std::move(s._val)), _name(std::move(s._name)), _isPair(s._isPair){};

    Signal1D& Signal1D::operator=(Signal1D&& other) noexcept {
        std::swap(_val, other._val);
        std::swap(_name, other._name);
        std::swap(_isPair, other._isPair);
        return *this;
    }

    Signal1D& Signal1D::operator=(const Signal1D& other){
        _val = other._val;
        _name = other._name;
        _isPair = other._isPair;
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
        s1._val.insert(s1._val.end(), s2._val.begin(), s2._val.end());
        return s1;
    }

    Signal1D operator+(const Signal1D& s1, const Signal1D& s2){
        Signal1D tmp(s1);
        return tmp += s2;
    }

    std::ostream& operator<<(std::ostream &out, const Signal1D &signal) {
        std::stringstream s;
        s << "# Representation of: " << signal._name << std::endl;
        for(auto tt: signal)
            s << tt << std::endl;
        return out << s.str();
    }

    Signal1D Signal1D::rampe() {
        if(Signal1D::_RAMPE.size())
            return Signal1D::_RAMPE;
        for(int i=0; i<256; ++i)
            Signal1D::_RAMPE.push_back(i);
        return Signal1D::_RAMPE;
    }

    Signal1D Signal1D::leleccum() {
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
}