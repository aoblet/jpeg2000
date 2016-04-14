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
    jpeg2000::test::lena_AMR_statistics(4);
    jpeg2000::test::lena_AMR_statistics(4);
    jpeg2000::test::lena2D_haar();
    jpeg2000::test::lena2D_AMR();
    jpeg2000::test::statsMeanVariance2D();
    jpeg2000::test::statsDebit();
    jpeg2000::test::quantify();
    jpeg2000::test::peakSignalNoiseRatio(8);
    jpeg2000::test::peakSignalNoiseRatio(7);
    jpeg2000::test::peakSignalNoiseRatio(6);
    jpeg2000::test::peakSignalNoiseRatio(5);
    jpeg2000::test::peakSignalNoiseRatio(4);
    jpeg2000::test::peakSignalNoiseRatio(3);
    jpeg2000::test::peakSignalNoiseRatio(2);
    jpeg2000::test::peakSignalNoiseRatio(1);
    jpeg2000::test::peakSignalNoiseRatio(0.5);
    jpeg2000::test::peakSignalNoiseRatio(0.25);
    jpeg2000::test::peakSignalNoiseRatio(0.15);
    jpeg2000::test::peakSignalNoiseRatio(0);
    jpeg2000::test::compressQuantlmIdx(4);
    jpeg2000::test::compressQuantlmIdx(2);
    jpeg2000::test::compressQuantlmIdx(1);
    jpeg2000::test::compressQuantlmIdx(5);
    return 0;
}