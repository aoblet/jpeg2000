//
// Created by alex on 22/10/15.
//

#ifndef JPEG2000_SIGNAL1D_HPP
#define JPEG2000_SIGNAL1D_HPP

#include <vector>
#include <iostream>
#include <string>
#include <iterator>
#include <fstream>

namespace jpeg2000{
    /**
     * Represents an 1D Signal. Values are stored as vector<double>.
     */
    class Signal1D{
    protected:
        std::string _name;          ///< Signal name, used for debug.
        std::vector<double> _val;   ///< Signal values.
        bool _isPair;               ///< Does the signal need to be pair. Default to true.

        static Signal1D _RAMPE;     ///< Rampe Signal "singleton". y = x for x = [0,..., 255]
        static Signal1D _LELECCUM;  ///< Leleccum Signal "singleton".

    public:
        // constructors
        Signal1D();
        Signal1D(int n);
        Signal1D(int n, double initVal);
        Signal1D(const std::string & name, int n, double initVal, bool isPair=true);
        Signal1D(const Signal1D& s);
        Signal1D(Signal1D&& s) noexcept;
        Signal1D(std::initializer_list<double> __l);

        int size() const;
        void push_back(double v);
        double operator[](int i) const;
        double& operator[](int i);

        Signal1D& operator=(Signal1D&& other) noexcept;
        Signal1D& operator=(const Signal1D& other);

        static Signal1D rampe();
        static Signal1D leleccum();

        // iterators
        std::vector<double>::iterator begin();
        std::vector<double>::const_iterator begin() const;
        std::vector<double>::iterator end();
        std::vector<double>::const_iterator end() const;

        friend std::ostream& operator<<(std::ostream& out, const Signal1D& signal);
        friend Signal1D& operator+=(Signal1D& s1, const Signal1D& s2);
        friend Signal1D operator+(const Signal1D& s1, const Signal1D& s2);

    };
    std::ostream& operator<<(std::ostream& out, const Signal1D& signal);
    Signal1D& operator+=(Signal1D& s1, const Signal1D& s2);
    Signal1D operator+(const Signal1D& s1, const Signal1D& s2);
}

#endif //JPEG2000_SIGNAL_HPP
