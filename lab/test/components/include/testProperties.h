#ifndef DIPACUS_TEST_COMPONENTS_PROPERTIES_H
#define DIPACUS_TEST_COMPONENTS_PROPERTIES_H

#include "DIPaCUS/base/Shapes.h"
#include "DIPaCUS/components/auxiliar/properties/boundingBox.h"
#include "DIPaCUS/components/Properties.h"

#include "DIPaCUS/derivates/Misc.h"

#include "logger/logger.h"

namespace DIPaCUS
{
    namespace Test
    {
        namespace Properties
        {
            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DGtal::Z2i::Point Point;
            typedef DIPaCUS::Properties::BoundingBox BoundingBox;


            bool testCurveBoundingBox(Logger& logger);
            bool testBoundingBoxImage(Logger& logger);
            bool testBoundingBoxCVImage(Logger& logger);

            bool runTest(std::ostream& os, const std::string& outputFolder, bool exportObjectsFlag=false);
        }
    }
}

#endif //DIPACUS_TEST_COMPONENTS_PROPERTIES_H
