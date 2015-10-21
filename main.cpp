#include <iostream>
#include <vector>
#include "filters.hpp"
#include <fstream>
#include <sstream>
#include "Signal1D.hpp"

using namespace std;


void printVec(const jpeg2000::Signal1D& v){
    for(double t: v)
        std::cout << t << ' ';
}

int main() {
    jpeg2000::Signal1D si(99, 50);
    jpeg2000::Signal1D si2();

    jpeg2000::Signal1D rampe;
    jpeg2000::Signal1D leleccum;

    for(int i=0; i<256; ++i)
        rampe.push_back(i);

    ifstream in("/home/alex/dev/filtering/jpeg2000/assets/leleccum.txt");
    string l;
    stringstream cast;
    double t;

    while(getline(in, l)){
        cast.clear();
        cast << l;

        if(cast>>t)
            leleccum.push_back(t);

    }
    jpeg2000::Signal1D rampeHaar = jpeg2000::filters::analyseHaar(rampe);
    jpeg2000::Signal1D leleccumHaar = jpeg2000::filters::analyseHaar(leleccum);

    std::stringstream s;
    for(auto tt: leleccumHaar)
        s<<tt << endl;
    ofstream out("haar.txt");
    out << s.str();
    out.close();
    return 0;

}