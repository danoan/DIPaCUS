#ifndef DIPACUS_TEST_BASE_SHAPES_H
#define DIPACUS_TEST_BASE_SHAPES_H

#include "DIPaCUS/base/Shapes.h"

#include "logger/logger.h"

namespace DIPaCUS
{
    namespace Test
    {
        namespace Shapes
        {
            typedef DIPaCUS::Shapes::DigitalSet DigitalSet;

            bool testTriangle(Logger& logger);
            bool testSquare(Logger& logger);
            bool testFlower(Logger& logger);
            bool testNGon(Logger& logger);
            bool testBall(Logger& logger);
            bool testEllipse(Logger& logger);
            bool testWave(Logger& logger);

            bool runTest(std::ostream& os, const std::string& outputFolder, bool exportObjectsFlag=false );
        }
    }
}

#endif //DIPACUS_TEST_BASE_SHAPES_H
