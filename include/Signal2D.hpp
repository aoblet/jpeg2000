#pragma once
#include "Signal1D.hpp"
#include <vector>

namespace jpeg2000{
    class Signal2D: public std::vector<Signal1D>{
    public:
        /**
         * Return the column at index i as a Signal1D
         * @param i: Column index to get
         */
        Signal1D col(int i) const;
        /**
         * Erase the column at a specific index with a given Signal1D
         */
        void eraseCol(int i, const Signal1D& s);
        void eraseRow(int i, const Signal1D& s);
        /**
         * @return The number of columns
         */
        int cols() const;
        /**
         * @return The number of rows
         */
        int rows() const;

        Signal2D extract(int width, int height) const;
    };
}
