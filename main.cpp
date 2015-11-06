#include "test.hpp"
#include "filters.hpp"

int main() {
    jpeg2000::test::rampe_analyse_synthese_haar();
    jpeg2000::test::rampe_analyse_synthese_haar97();
    jpeg2000::test::leleccum_analyse_synthese_haar();
    jpeg2000::test::leleccum_analyse_synthese_haar97();
    jpeg2000::test::rampe_analyse_synthese_lifting97();
    jpeg2000::test::leleccum_analyse_synthese_lifting97();
    jpeg2000::test::lena_haar_haar97_lifting97();
    jpeg2000::test::lena_analyse_synthese_AMR();
    return 0;
}