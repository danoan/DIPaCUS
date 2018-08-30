#ifndef DIPACUS_DERIVATES_MISC_H
#define DIPACUS_DERIVATES_MISC_H

#include "DGtal/helpers/StdDefs.h"

#include <DGtal/shapes/implicit/ImplicitBall.h>
#include <DGtal/shapes/Shapes.h>
#include "DGtal/kernel/sets/DigitalSetInserter.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/images/SimpleThresholdForegroundPredicate.h"

#include "DIPaCUS/components/SetOperations.h"
#include "DIPaCUS/components/Neighborhood.h"
#include "DIPaCUS/components/Morphology.h"
#include "DIPaCUS/components/Transform.h"

namespace DIPaCUS
{
    namespace Misc {

        class DigitalBallIntersection {
        public:
            typedef unsigned int Radius;

            typedef DGtal::Z2i::Space Space;
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::Domain Domain;


            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DGtal::ImplicitBall<Space> EuclideanBall;

        public:
            DigitalBallIntersection(Radius r,
                                    const DigitalSet &intersectWith);

            void operator()(DigitalSet &intersectionSet,
                            Point center);

            void digitalBall(DigitalSet &db,
                             Point center,
                             int radius);

        private:
            Radius _r;
            const DigitalSet &_ds;
        };


        template<typename TNeighborhood>
        struct DigitalBoundary {
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::DigitalSet DigitalSet;

            typedef DGtal::ImageContainerBySTLVector<Domain, unsigned char> Image2D;
            typedef TNeighborhood NeighborhoodPredicate;


            typedef DGtal::DigitalSetInserter<DigitalSet> DigitalSetInserter;

            DigitalBoundary(DigitalSet &boundaryDS,
                            const DigitalSet &originalDS);
        };


        struct FindIPNIS {
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;

            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DigitalSet::ConstIterator DigitalSetIterator;

            FindIPNIS(Point &ipnil,
                      const DigitalSet &inputSet,
                      const DigitalSet &invalidSet);
        };

        struct FillInterior {
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;

            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DigitalSet::ConstIterator DigitalSetIterator;

            FillInterior(DigitalSet &simplyConnectedSet,
                         const Point &interiorPoint,
                         const DigitalSet &boundary);
        };

        struct NoHoles {
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;

            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DGtal::DigitalSetInserter<DigitalSet> DigitalSetInserter;

            typedef DigitalBoundary<Neighborhood::FourNeighborhoodPredicate<DigitalSet>> FourBoundary;

            NoHoles(DigitalSet &noHoles,
                    const DigitalSet &dsIn);
        };

        struct ThickBorder {
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;

            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DGtal::DigitalSetInserter<DigitalSet> DigitalSetInserter;

            ThickBorder(DigitalSet &thickBorder,
                        const DigitalSet &dsIn,
                        int thickness);
        };

        struct ComputeBoundaryCurve
        {
            typedef DGtal::Z2i::Curve Curve;
            typedef DGtal::Z2i::KSpace KSpace;
            typedef DGtal::Z2i::SCell SCell;
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::Domain Domain;

            typedef DGtal::SurfelAdjacency<KSpace::dimension> SurfelAdjacency;
            typedef DGtal::Surfaces<KSpace> Surfaces;

            typedef DGtal::ImageContainerBySTLVector<Domain, unsigned char> Image2D;
            typedef DGtal::functors::SimpleThresholdForegroundPredicate<Image2D> ThreshPredicate;

            ComputeBoundaryCurve(const Image2D &image,
                                 Curve &boundCurve,
                                 unsigned int thresh_value);

            ComputeBoundaryCurve(const Image2D& image,
                                 Curve& boundCurve,
                                 unsigned int thresh_value,
                                 SCell imageBel);
        };

    }
}

#include "Misc.hpp"

#endif //DIPACUS_DERIVATES_MISC_H
