#include <data.h>
#include <testNeighborhood.h>
#include <testProperties.h>
#include <testSetOperations.h>
#include <testTransform.h>
#include "testMorphology.h"

int main()
{
    Test::Morphology::testDilate(1,1,Test::Morphology::Data::square11DS,Test::Morphology::Data::square13DS);
    Test::Morphology::testDilate(2,1,Test::Morphology::Data::square9DS,Test::Morphology::Data::square13DS);
    Test::Morphology::testDilate(1,2,Test::Morphology::Data::square9DS,Test::Morphology::Data::square13DS);


    Test::Morphology::testErosion(1,1,Test::Morphology::Data::square11DS,Test::Morphology::Data::square9DS);
    Test::Morphology::testErosion(2,1,Test::Morphology::Data::square13DS,Test::Morphology::Data::square9DS);
    Test::Morphology::testErosion(1,2,Test::Morphology::Data::square13DS,Test::Morphology::Data::square9DS);

    Test::Morphology::testOpening(1,1,Test::Morphology::Data::square11DS);
    Test::Morphology::testOpening(2,1,Test::Morphology::Data::square11DS);
    Test::Morphology::testOpening(1,2,Test::Morphology::Data::square11DS);
    Test::Morphology::testOpening(1,5,Test::Morphology::Data::square11DS);


    Test::Morphology::testClosing(1,1,Test::Morphology::Data::square11DS);
    Test::Morphology::testClosing(2,1,Test::Morphology::Data::square11DS);
    Test::Morphology::testClosing(1,2,Test::Morphology::Data::square11DS);
    Test::Morphology::testClosing(1,5,Test::Morphology::Data::square11DS);

    Test::Neighborhood::testFourOnBall();
    Test::Neighborhood::testEightOnBall();
    Test::Neighborhood::testComplementEquivalence();

    Test::Properties::testExecution();

    Test::SetOperations::testExecution();

    Test::Transform::testExecution();

    return 0;
}