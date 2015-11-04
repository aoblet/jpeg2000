#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <iterator>

namespace jpeg2000{
    /**
     * Represents an 1D Signal. Values are stored as vector<double>.
     */
    class Signal1D{
    protected:
        std::string _name;          ///< Signal name, used for debug.
        std::vector<double> _val;   ///< Signal values.

        static Signal1D _RAMPE;     ///< Rampe Signal "singleton". y = x for x = [0,..., 255]
        static Signal1D _LELECCUM;  ///< Leleccum Signal "singleton".

    public:
        static const Signal1D& RAMPE();     ///< "Singleton" getter of constant rampe signal
        static const Signal1D& LELECCUM();  ///< "Singleton" getter of constant leleccum signal
        static Signal1D readFromFile(const std::string& filePath);

        // constructors
        Signal1D();
        Signal1D(int n);
        Signal1D(int n, double initVal);
        Signal1D(const std::string & name, int n, double initVal);
        Signal1D(const std::string & name);
        Signal1D(const Signal1D& s);
        Signal1D(Signal1D&& s) noexcept;
        Signal1D(std::initializer_list<double> __l);

        int size() const;
        void push_back(double v);

        /**
         * Concat two signals together.
         */
        Signal1D concat(const Signal1D& other) const;

        /**
         * Extracts a sub signal from a range
         * @param f: from index inclusive
         * @param t: to index inclusive: if -1 extract to the end like python style
         */
        Signal1D extract(int f, int t=-1) const;
        double operator[](int i) const;
        double& operator[](int i);
        std::string name() const;
        void setName(const std::string & name);

        /**
         * Double symmetry operation.
         * @param i: index associated to signal
         * @return A mirror symmetry value.
         */
        double mirrorSymmetry(int i) const;

        Signal1D& operator=(Signal1D&& other) noexcept;
        Signal1D& operator=(const Signal1D& other);

        /**
         * Append a double to the signal.
         */
        Signal1D& operator+=(const double n);

        // iterators: iterate over vector
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