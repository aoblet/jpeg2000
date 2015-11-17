#include "Signal2D.hpp"
#include "SignalException.hpp"

namespace jpeg2000{
    Signal1D Signal2D::col(int i) const{
        if(i<0 || i>=(*this)[0].size())
            throw SignalException::OutOfRange("");

        Signal1D tmp;
        for(int j=0; j<size(); ++j)
            tmp += (*this)[j][i];
        return tmp;
    }

    void Signal2D::eraseCol(int i, const Signal1D& s){
        // add rows if the matrix is too small
        int missingRows = s.size() - rows();
        if(missingRows > 0){
            for(int j=0; j<missingRows; ++j)
                push_back(Signal1D());
        }

        // erase the col
        for(int j=0; j<s.size(); ++j)
            (*this)[j][i] = s[j];
    }

    void Signal2D::eraseRow(int i, const Signal1D& s){
        for(int j=0; j<s.size(); ++j){
            (*this)[i][j] = s[j];
        }
    }
    int Signal2D::cols() const{
        return empty() ? 0 : (*this)[0].size();
    }

    int Signal2D::rows() const{
        return (int)size();
    }

    Signal2D Signal2D::extract(int width, int height) const{
        Signal2D res;

        for(int y=0; y<height; y++){
            Signal1D tmp;
            for(int x=0; x<width; ++x){
                tmp.push_back((*this)[y][x]);
            }
            res.push_back(tmp);
        }
        return res;
    }
}
