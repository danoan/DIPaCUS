#ifndef DIPACUS_TEST_COMPONENTS_SETOPERATIONS_H
#define DIPACUS_TEST_COMPONENTS_SETOPERATIONS_H

#include <DGtal/helpers/StdDefs.h>

#include "DIPaCUS/components/SetOperations.h"
#include "DIPaCUS/base/Shapes.h"

#include "logger/logger.h"

namespace DIPaCUS
{
    namespace Test
    {
        namespace SetOperations
        {
            typedef DGtal::Z2i::DigitalSet DigitalSet;

            bool testSetDifference(Logger& logger);
            bool testSetIntersection(Logger& logger);

            bool runTest(std::ostream& os, const std::string& outputFolder, bool exportObjectsFlag=false);
        }
    }
}

#endif //DIPACUS_TEST_COMPONENTS_SETOPERATIONS_H
