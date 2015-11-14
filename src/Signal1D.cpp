#include "Signal1D.hpp"
#include <sstream>
#include <boost/filesystem.hpp>
#include <fstream>
#include <algorithm>
#include "assets.hpp"

namespace jpeg2000{
    Signal1D Signal1D::_RAMPE("RAMPE");
    Signal1D Signal1D::_LELECCUM("LELECCUM");
    Signal1D Signal1D::_LENA("LELECCUM");

    Signal1D::Signal1D():_val(), _name("1D Signal"){};

    Signal1D::Signal1D(const std::string & name, int n, double initVal):
            _val(std::vector<double>::size_type(n), initVal),
            _name(name){};

    Signal1D::Signal1D(const std::string& name): Signal1D(name, 0, 0){}
    Signal1D::Signal1D(int n, double initVal): Signal1D("1D Signal", n, initVal){}
    Signal1D::Signal1D(int n) : Signal1D(n, 0){}
    Signal1D::Signal1D(const Signal1D& s){
        if(this == &s)
            return;
        _val = s._val;
        _name = s._name;
    }
    Signal1D::Signal1D(std::initializer_list<double> __l): _val(__l), _name("1D Signal"){}

    Signal1D::Signal1D(Signal1D&& s) noexcept :_val(std::move(s._val)), _name(std::move(s._name)){};

    Signal1D& Signal1D::operator=(Signal1D&& other) noexcept {
        if(this == &other)
            return *this;

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

    void Signal1D::toFile(const std::string& filePath){
        std::ofstream out(filePath);
        if(!out.is_open()){
            std::cout << "Warning: Signal1D::toFile - cannot save at the specified location: " + filePath;
            return;
        }
        out << *this;
    }

    Signal1D& Signal1D::operator=(const Signal1D& other){
        if(this == &other)
            return *this;

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
        return _val.at((ulong)i);
    }

    double& Signal1D::operator[](int i){
        return _val.at((ulong)i);
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

    const Signal1D& Signal1D::RAMPE(){
        if(Signal1D::_RAMPE.size())
            return Signal1D::_RAMPE;

        for(int i=0; i<256; ++i)
            Signal1D::_RAMPE.push_back(i);
        return Signal1D::_RAMPE;
    }

    Signal1D Signal1D::readFromFile(const std::string& filePath){
        std::ifstream in(filePath);
        std::string l;
        std::stringstream cast;
        double t;
        Signal1D tmp;

        while(getline(in, l)){
            cast.clear();
            cast << l;

            if(cast>>t)
                tmp.push_back(t);
        }
        return tmp;
    }

    const Signal1D& Signal1D::LELECCUM(){
        if(Signal1D::_LELECCUM.size())
            return Signal1D::_LELECCUM;

        Signal1D::_LELECCUM = std::move(Signal1D::readFromFile(assets::paths::LELECCUM_FILE));
        Signal1D::_LELECCUM.setName("LELECCUM");
        return Signal1D::_LELECCUM;
    }

    const Signal1D& Signal1D::LENA(){
        if(Signal1D::_LENA.size())
            return Signal1D::_LENA;

        Signal1D::_LENA = std::move(Signal1D::readFromFile(assets::paths::LENA_FILE));
        Signal1D::_LENA.setName("LenaMiddleLine");
        return Signal1D::_LENA;
    }

    Signal1D& Signal1D::operator+=(const double n){
        push_back(n);
        return *this;
    }

    Signal1D Signal1D::concat(const Signal1D& other) const{
        if(!other.size())
            return *this;

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

    bool Signal1D::isEven() const{
        return !(size()%2);
    }

    double Signal1D::mirrorSymmetry(int i) const{
        const int doubleSize = 2*size();

        // if the index is greater than the signal itself: take the modulo
        if (std::abs(i) >= doubleSize)
            return (*this)[std::abs(i)%size()];
        if (i < 0)
            return (*this)[i * -1];
        if (i >= size())
            return (*this)[doubleSize -2 -i];
        return (*this)[i];
    }

    double Signal1D::max() const{
        if(!_val.size())
            return 0;
        return *std::max_element(_val.begin(), _val.end());
    }

    double Signal1D::min() const{
        if(!_val.size())
            return 0;
        return *std::min_element(_val.begin(), _val.end());
    }
    double Signal1D::mean() const{
        if(!_val.size())
            return 0;
        return std::accumulate(_val.begin(), _val.end(), 0.0) / _val.size();
    }
}
