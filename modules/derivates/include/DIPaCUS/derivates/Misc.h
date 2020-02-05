#ifndef DIPACUS_DERIVATES_MISC_H
#define DIPACUS_DERIVATES_MISC_H

#include <DGtal/helpers/StdDefs.h>

#include <DGtal/shapes/implicit/ImplicitBall.h>
#include <DGtal/shapes/Shapes.h>
#include <DGtal/kernel/sets/DigitalSetInserter.h>
#include <DGtal/topology/helpers/Surfaces.h>
#include <DGtal/images/SimpleThresholdForegroundPredicate.h>

#include "DIPaCUS/base/Shapes.h"

#include "DIPaCUS/components/SetOperations.h"
#include "DIPaCUS/components/Neighborhood.h"
#include "DIPaCUS/components/Properties.h"
#include "DIPaCUS/components/Morphology.h"
#include "DIPaCUS/components/Transform.h"

namespace DIPaCUS
{
    /**
     *
     * \brief Set of complex operations involving two or more components
     *
     * It operates on grayscale images only.
     * \author Daniel Martins Antunes
     * \version 0.1
     * \date 2018/08/27
    */
    namespace Misc
    {
        typedef unsigned int Radius;
        typedef unsigned int ThresholdValue;
        typedef unsigned int Thickness;

        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::Z2i::KSpace KSpace;
        typedef DGtal::Z2i::Point Point;
        typedef DGtal::Z2i::DigitalSet DigitalSet;

        typedef DGtal::ImageContainerBySTLVector<Domain, unsigned char> Image2D;

        typedef DGtal::Z2i::Curve Curve;
        typedef DGtal::Z2i::SCell SCell;

        typedef Curve::ConstIterator SCellIterator;

        typedef std::set<Point> ConnectedComponent;
        typedef std::set<Point> PointMarker;

        /**
         * \brief Computes intersection of any digital object with a
         * given digital ball.
         */
        class DigitalBallIntersection
        {
        public:
            typedef DGtal::Z2i::Space Space;
            typedef DGtal::Z2i::Domain Domain;

        private:
            /**
             * \brief Extends the domain of a digital set in order
             * to accomodate a ball around its original limits.
             *
             * During the intersection computation we need to construct
             * a digital set in which ball and intersectWith set are merged.
             * This function guarantees that such set has the proper domain.
             * @param ds DigitalSet to be extended
             * @param r Radius of the digital ball
             * @return
             */
            static DigitalSet extendDS(const DigitalSet& ds,Radius r);


            /**
             * \brief Extends the domain of a digital set in order
             * to accomodate a ball around its original limits.
             *
             * During the intersection computation we need to construct
             * a digital set in which ball and intersectWith set are merged.
             * This function guarantees that such set has the proper domain.
             * @param ds DigitalSet to be extended
             * @param r Radius of the digital ball
             * @return
             */
            static Domain extendDomain(const DigitalSet& ds,Radius r);

        public:
            DigitalBallIntersection(Radius r,
                                    const DigitalSet &intersectWith);

            template<class TPointSet>
            void operator()(TPointSet &intersectionSet,
                            Point center)
            {
                DIPaCUS::SetOperations::setIntersection(intersectionSet, _ball, _ds, center);
            }

            const Domain& domain(){ return _extDomain; }
            const DigitalSet& digitalBall(){ return _ball; }

        private:
            Radius _r;
            DigitalSet _ball;
            const DigitalSet _ds;
            const Domain _extDomain;
        };

        /**
         * \brief Computes the pixel digital boundary of digital set
         * dsIn accordingly with neighborhood type (four or eight
         * connected ).
         *
         * @tparam TNeighborhood Connectedeness predicate. \refitem Neighborhood
         * @param dsOut Pixel boundary output
         * @param dsIn Digital set input\
         * @param t Thickness of contour
         */
        template<typename TNeighborhood>
        void digitalBoundary(DigitalSet &dsOut,
                             const DigitalSet &dsIn,
                             Thickness t=1);


        /**
         * \brief Given a closed boundary, the domain is divided in two regions A and
         * B. Given a point p, it must belong to A, B or the boundary itself. Denote
         * such region R(p). This function fills out all the region R(p).
         *
         * @param dsOut Filled out digital set
         * @param pt Point in the domain of boundIn
         * @param boundIn Pixel boundary
         */
        void fillInterior(DigitalSet &dsOut,
                          const Point &pt,
                          const DigitalSet &boundIn);


        /**
         * \brief Returns a border of given thickness around the digital set
         * @param dsOut Border of the digital set
         * @param dsIn Digital set input
         * @param t Thickness of border in number of pixels
         */
        void getBorder(DigitalSet &dsOut,
                       const DigitalSet &dsIn,
                       Thickness t);


        /**
         * \brief Compute linel boundary for a given grayscale image
         *
         * @param boundOut Linel boundary as a DGtal::Z2i::Curve
         * @param imgIn Grayscale image
         * @param tv Only pixels with internsity above tv are considered
         * part of the image
         */
        void computeBoundaryCurve(Curve &boundOut,
                                  const Image2D &imgIn,
                                  ThresholdValue tv);


        /**
        * \brief Compute linel boundary for a given digital set
         *
         * @param boundOut Linel boundary as a DGtal::Z2i::Curve
         * @param dsIn Digital set input
         */
        void computeBoundaryCurve(Curve& boundOut,
                                  const DigitalSet& dsIn);


        /**
         * \brief Curves in 2D may be oriented clock or counterclock wise. This
         * function inverts its orientation.
         *
         * @param KImage Khalismsky space of the curve
         * @param begin Curve iterator begin
         * @param end Curve iterator end
         * @param cOut Output curve
         * @tparam TSCellIterator An iterator which value type is a SCell
         */
        template<class TSCellIterator>
        void invertCurve(Curve& cOut,
                         const KSpace& KImage,
                         TSCellIterator begin,
                         TSCellIterator end);

        /**
         * \brief Given an oriented curve, it returns a compact set.
         *
         * @param dsOut Compact set.
         * @param itb Curve iterator begin
         * @param ite Curve iterator end
         * @param ccw True if curve is oriented counterclock-wise
         * @tparam TSCellIterator An iterator which value type is a SCell
         */
        template<class TSCellIterator>
        void compactSetFromClosedCurve(DigitalSet& dsOut,
                                       TSCellIterator itb,
                                       TSCellIterator ite,
                                       bool ccw=true);

        /**
         * \brief Return all the 4-connected components in a digital set
         *
         * @param vcc Vector of ConnectedComponent
         * @param ds Digital Set
         */

        void getConnectedComponents( std::vector<ConnectedComponent>& vcc, const DigitalSet& ds);

        /**
         * \brief Marks all points in the same connected component than p and return such ConnectedComponent
         * @param cc ConnectedComponent
         * @param p Point p inside the connected component
         * @param markers Set of marked points
         * @param ds DigitalSet
         */
        void exploreComponent(ConnectedComponent& cc,Point& p, PointMarker& markers, const DigitalSet& ds);


    }
}

#include "Misc.hpp"

#endif //DIPACUS_DERIVATES_MISC_H
