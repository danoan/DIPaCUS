#ifndef DIPACUS_COMPONENTS_NEIGHBORHOOD_H
#define DIPACUS_COMPONENTS_NEIGHBORHOOD_H

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

        /**
        * \brief Predicate to identify points in a 8-connected boundary.
        * \author Daniel Martins Antunes
        * \version 0.1
        * \date 2018/08/27
        */
        class EightNeighborhoodPredicate {
        public:
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::DigitalSet DigitalSet;

            /**
             * \brief Constructor.
             * @param digitalSet DGtal DigitalSet in which the precidate is evaluated.
             */
            explicit EightNeighborhoodPredicate(const DigitalSet &digitalSet);

            /**
             * \brief Test if a point belongs to the 8-connected boundary of digitalSet.
             * @param aPoint Point belonging to digital set.
             * @return True if aPoint belongs to the 8-connected boundary of digitalSet.
             */
            bool operator()(const Point &aPoint) const;


            /**
             * \brief Test if a point belongs to the 8-connected boundary of digitalSet.
             * @param it ConstIterator from a digitalSet domain.
             * @return True if aPoint belongs to the 8-connected boundary of digitalSet.
             */
            bool operator()(const Domain::ConstIterator &it) const;


        private:
            const DigitalSet &myDigitalSet;
            Point filter[4] = {Point(0, 1), Point(1, 0),
                               Point(-1, 0), Point(0, -1)};

            Point lowerBound, upperBound;

        };


        /**
        * \brief Predicate to identify points in a 4-connected boundary.
        * \author Daniel Martins Antunes
        * \version 0.1
        * \date 2018/08/27
        */
        class FourNeighborhoodPredicate {
        public:
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::DigitalSet DigitalSet;

            /**
             * \brief Constructor.
             * @param digitalSet DGtal DigitalSet in which the precidate is evaluated.
             */
            explicit FourNeighborhoodPredicate(const DigitalSet &digitalSet);

            /**
             * \brief Test if a point belongs to the 4-connected boundary of digitalSet.
             * @param aPoint Point belonging to digital set.
             * @return True if aPoint belongs to the 4-connected boundary of digitalSet.
             */
            bool operator()(const Point &aPoint) const;


            /**
             * \brief Test if a point belongs to the 4-connected boundary of digitalSet.
             * @param it ConstIterator from a digitalSet domain.
             * @return True if aPoint belongs to the 4-connected boundary of digitalSet.
             */
            bool operator()(const Domain::ConstIterator &it) const;


        private:
            const DigitalSet &myDigitalSet;
            Point filter[8] = {Point(0, 1), Point(1, 0),
                               Point(-1, 0), Point(0, -1),
                               Point(1, 1), Point(-1, -1),
                               Point(1, -1), Point(-1, 1)
            };

            Point lowerBound, upperBound;

        };
    }
}


#endif //DIPACUS_COMPONENTS_NEIGHBORHOOD_H