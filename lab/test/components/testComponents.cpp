#include <data.h>
#include "testMorphology.h"

using namespace Test;

int main()
{
    Morphology::testDilate(1,1,Test::Morphology::Data::square11DS,Test::Morphology::Data::square13DS);
    Morphology::testDilate(2,1,Test::Morphology::Data::square9DS,Test::Morphology::Data::square13DS);
    Morphology::testDilate(1,2,Test::Morphology::Data::square9DS,Test::Morphology::Data::square13DS);


    Morphology::testErosion(1,1,Test::Morphology::Data::square11DS,Test::Morphology::Data::square9DS);
    Morphology::testErosion(2,1,Test::Morphology::Data::square13DS,Test::Morphology::Data::square9DS);
    Morphology::testErosion(1,2,Test::Morphology::Data::square13DS,Test::Morphology::Data::square9DS);

    Morphology::testOpening(1,1,Test::Morphology::Data::square11DS);
    Morphology::testOpening(2,1,Test::Morphology::Data::square11DS);
    Morphology::testOpening(1,2,Test::Morphology::Data::square11DS);
    Morphology::testOpening(1,5,Test::Morphology::Data::square11DS);


    Morphology::testClosing(1,1,Test::Morphology::Data::square11DS);
    Morphology::testClosing(2,1,Test::Morphology::Data::square11DS);
    Morphology::testClosing(1,2,Test::Morphology::Data::square11DS);
    Morphology::testClosing(1,5,Test::Morphology::Data::square11DS);

    return 0;
}