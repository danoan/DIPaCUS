#ifndef DIPACUS_TEST_COMPONENTS_NEIGHBORHOOD_H
#define DIPACUS_TEST_COMPONENTS_NEIGHBORHOOD_H

#include <DGtal/images/SimpleThresholdForegroundPredicate.h>

#include "DIPaCUS/base/Representation.h"
#include "DIPaCUS/base/Shapes.h"

#include "DIPaCUS/components/Neighborhood.h"

#include "DIPaCUS/derivates/Misc.h"

#include "logger/logger.h"

namespace DIPaCUS
{
    namespace Test
    {
        namespace Neighborhood
        {
            typedef DGtal::Z2i::DigitalSet DigitalSet;

            bool testFourOnBall(Logger& logger);
            bool testEightOnBall(Logger& logger);
            bool testComplementEquivalence(Logger& logger);

            bool runTest(std::ostream& os, const std::string& outputFolder, bool exportObjectsFlag=false);



            namespace Internal
            {
                typedef DGtal::Z2i::Curve Curve;

                template<typename TPredicate>
                DigitalSet digitalBoundary(const DigitalSet& ds);

                DigitalSet digitalComplement(const DigitalSet& ds);

            }
        }
    }
}
#include "testNeighborhood.hpp"

#endif //DIPACUS_TEST_COMPONENTS_NEIGHBORHOOD_H
