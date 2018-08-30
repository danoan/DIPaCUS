#ifndef DIPACUS_MODULES_NEIGHBORHOOD_H
#define DIPACUS_MODULES_NEIGHBORHOOD_H

#include <iostream>

#include <DGtal/helpers/StdDefs.h>
#include "DGtal/base/Common.h"
#include "DGtal/images/CConstImage.h"
#include "DGtal/base/ConstAlias.h"

#include "boost/concept/assert.hpp"
#include "boost/assert.hpp"

namespace DIPaCUS
{
    namespace Neighborhood {
        template<typename DigitalSet>
        class FourNeighborhoodPredicate {
        public:
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;

            FourNeighborhoodPredicate(const DigitalSet &DS);

            bool operator()(const Point &aPoint) const;

            bool operator()(const Domain::ConstIterator &it) const;


        private:
            const DigitalSet &myDigitalSet;
            Point filter[4] = {Point(0, 1), Point(1, 0),
                               Point(-1, 0), Point(0, -1)};

            Point lowerBound, upperBound;


        protected:
            FourNeighborhoodPredicate();

        };


        template<typename DigitalSet>
        class EightNeighborhoodPredicate {
        public:
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;

            EightNeighborhoodPredicate(const DigitalSet &DS);

            bool operator()(const Point &aPoint) const;

            bool operator()(const Domain::ConstIterator &it) const;


        private:
            const DigitalSet &myDigitalSet;
            Point filter[8] = {Point(0, 1), Point(1, 0),
                               Point(-1, 0), Point(0, -1),
                               Point(1, 1), Point(-1, -1),
                               Point(1, -1), Point(-1, 1)
            };

            Point lowerBound, upperBound;


        protected:
            EightNeighborhoodPredicate();

        };
    }
}

#include "Neighborhood.hpp"


#endif //DIPACUS_MODULES_NEIGHBORHOOD_H
