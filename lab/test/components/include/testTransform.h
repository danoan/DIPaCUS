#ifndef DIPACUS_TEST_COMPONENTS_TRANSFORM_H
#define DIPACUS_TEST_COMPONENTS_TRANSFORM_H

#include <DGtal/helpers/StdDefs.h>

#include "DIPaCUS/base/Shapes.h"
#include "DIPaCUS/base/Representation.h"
#include "DIPaCUS/components/Transform.h"

#include "logger/logger.h"

namespace DIPaCUS
{
    namespace Test
    {
        namespace Transform
        {
            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;
            typedef DIPaCUS::Representation::Image2D Image2D;

            bool testResize(Logger& logger);
            bool testInvertColors(Logger& logger);
            bool testAddBorder(Logger& logger);
            bool testBottomLeftBoundingBoxAtOrigin(Logger& logger);

            bool runTest(std::ostream& os, const std::string& outputFolder, bool exportObjectsFlag);
        }
    }
}

#endif //DIPACUS_TEST_COMPONENTS_TRANSFORM_H
