#ifndef DIPACUS_TEST_DERIVATES_TESTMISC_H
#define DIPACUS_TEST_DERIVATES_TESTMISC_H

#include <DGtal/helpers/StdDefs.h>

#include "DIPaCUS/base/Shapes.h"
#include "DIPaCUS/derivates/Misc.h"


#include "data.h"
#include "logger/logger.h"

namespace DIPaCUS
{
    namespace Test
    {
        namespace Misc
        {
            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Curve Curve;

            typedef DGtal::ImageContainerBySTLVector<DGtal::Z2i::Domain, unsigned char> Image2D;

            bool testDigitalBallIntersection(Logger& logger);
            bool testDigitalBoundaryAndFillInterior(Logger& logger);

            bool testGetBorder(Logger& logger);
            bool testInvertCurve(Logger& logger);

            bool testComputeBoundaryCurve(const Image2D& imgIn,
                                          const std::string& name,
                                          Logger& logger);

            bool testComputeBoundaryCurve(Logger& logger);
            bool testCompactSetFromClosedCurve(Logger& logger);

            bool runTest(std::ostream& os,
                         const std::string& outputFolder,
                         bool exportObjectsFlag=false);

        }
    }
}

#endif //DIPACUS_TEST_DERIVATES_TESTMISC_H
