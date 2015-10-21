#include <iostream>
#include <vector>
#include "filters.hpp"
#include <fstream>
#include <sstream>

using namespace std;

void printVec(const vector<double>& v){
    for(double t: v)
        std::cout << t << ' ';
}

int main() {
    vector<double> rampe;
    for(int i=0; i<256; ++i)
        rampe.push_back(i);

    vector<double> tmp = jpeg2000::filters::analyseHaar(rampe);
    std::stringstream s;
    for(auto t: tmp)
        s<<t << endl;
    ofstream out("haar.txt");
    out << s.str();
    out.close();
    return 0;

}