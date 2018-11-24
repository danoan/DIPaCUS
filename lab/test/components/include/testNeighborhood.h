#ifndef DIPACUS_TESTNEIGHBORHOOD_H
#define DIPACUS_TESTNEIGHBORHOOD_H

#include <DGtal/images/SimpleThresholdForegroundPredicate.h>
#include <DIPaCUS/base/Representation.h>

#include <DIPaCUS/components/Neighborhood.h>
#include <DIPaCUS/base/Shapes.h>

#include <utils/utils.h>

namespace Test
{
    namespace Neighborhood
    {
        typedef DGtal::Z2i::DigitalSet DigitalSet;

        void testFourOnBall();
        void testEightOnBall();

        void testComplementEquivalence();

        namespace Internal
        {
            typedef DGtal::Z2i::Curve Curve;

            template<typename TPredicate>
            DigitalSet digitalBoundary(const DigitalSet& ds);

            DigitalSet digitalComplement(const DigitalSet& ds);

        }
    }
}

#include "testNeighborhood.hpp"

#endif //DIPACUS_TESTNEIGHBORHOOD_H
