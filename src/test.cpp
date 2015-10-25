//
// Created by alex on 25/10/15.
//

#include "test.hpp"
#include <fstream>
#include "Signal1D.hpp"
#include "filters.hpp"

void jpeg2000::test::leleccum_analyse_synthese_haar97() {
    using namespace std;
    system("mkdir -p haar97");

    jpeg2000::Signal1D leleccum(jpeg2000::Signal1D::leleccum());

    ofstream fileLeleccum("haar97/leleccum.txt");
    ofstream fileLeleccumHaar("haar97/leleccumHaar.txt");
    ofstream fileLeleccumHaarSynth("haar97/leleccumHaarSynth.txt");

    fileLeleccum << leleccum;
    fileLeleccumHaar << jpeg2000::filters::analyseHaar(leleccum);
    fileLeleccumHaarSynth << jpeg2000::filters::synthesisHaar(jpeg2000::filters::analyseHaar(leleccum));
}

void jpeg2000::test::leleccum_analyse_synthese_haar() {
    using namespace std;
    system("mkdir -p haar");

    jpeg2000::Signal1D leleccum(jpeg2000::Signal1D::leleccum());

    ofstream fileLeleccum("haar/leleccum.txt");
    ofstream fileLeleccumHaar("haar/leleccumHaar.txt");
    ofstream fileLeleccumHaarSynth("haar/leleccumHaarSynth.txt");

    fileLeleccum << leleccum;
    fileLeleccumHaar << jpeg2000::filters::analyseHaar97(leleccum);
    fileLeleccumHaarSynth << jpeg2000::filters::synthesisHaar97(jpeg2000::filters::analyseHaar97(leleccum));
}

void jpeg2000::test::rampe_analyse_synthese_haar97() {
    using namespace std;
    system("mkdir -p haar97");

    jpeg2000::Signal1D rampe(jpeg2000::Signal1D::rampe());
    jpeg2000::Signal1D rampeHaar(jpeg2000::filters::analyseHaar97(rampe));

    ofstream fileRampe("haar/rampe.txt");
    ofstream fileRampeHaar("haar/rampeHaar.txt");
    ofstream fileRampeHaarSynth("haar/rampeHaarSynth.txt");

    fileRampe << rampe;
    fileRampeHaar << jpeg2000::filters::analyseHaar97(rampeHaar);
    fileRampeHaarSynth << jpeg2000::filters::synthesisHaar97(jpeg2000::filters::analyseHaar97(rampe));
}

void jpeg2000::test::rampe_analyse_synthese_haar() {
    using namespace std;
    system("mkdir -p haar");

    jpeg2000::Signal1D rampe(jpeg2000::Signal1D::rampe());
    jpeg2000::Signal1D rampeHaar(jpeg2000::filters::analyseHaar(rampe));

    ofstream fileRampe("haar/rampe.txt");
    ofstream fileRampeHaar("haar/rampeHaar.txt");
    ofstream fileRampeHaarSynth("haar/rampeHaarSynth.txt");

    fileRampe << rampe;
    fileRampeHaar << jpeg2000::filters::analyseHaar(rampeHaar);
    fileRampeHaarSynth << jpeg2000::filters::synthesisHaar(jpeg2000::filters::analyseHaar(rampe));
}
