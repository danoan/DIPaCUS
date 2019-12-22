#ifndef DIPACUS_COMPONENTS_SET_OPERATIONS_H
#define DIPACUS_COMPONENTS_SET_OPERATIONS_H


#include <DGtal/helpers/StdDefs.h>
#include <DGtal/kernel/sets/DigitalSetInserter.h>

namespace DIPaCUS
{
    /**
     * \brief Set operations on DGtal digital sets.
     *
     * \author Daniel Martins Antunes
     * \version 0.1
     * \date 2018/08/27
     */
    namespace SetOperations
    {
        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::Z2i::Point Point;
        typedef DGtal::PointVector<2,double> RealPoint;

        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::DigitalSetInserter<DigitalSet> DigitalSetInserter;

        /**
         * \brief Computes the difference set between two digital sets.
         * @param differenceSet Difference set A-B
         * @param A First set
         * @param B Second set
         */
        void setDifference(DigitalSet &differenceSet,
                           const DigitalSet &A,
                           const DigitalSet &B);

        /**
         * \brief Computes the intersection set between two digital sets.
         * @param digitalIntersection Intersection set of A and B
         * @param A First set
         * @param B Second set
         */
        template<class TPointSet>
        void setIntersection(TPointSet &digitalIntersection,
                             const DigitalSet &A,
                             const DigitalSet &B)
        {
            for (auto it = A.begin(); it != A.end(); ++it)
            {
                if (B(*it)) digitalIntersection.insert(*it);
            }
        }


        /**
         * \brief Computes the intersection set between two digital sets.
         * @param digitalIntersection Intersection set of A and B
         * @param A First set
         * @param B Second set
         * @param translation Every point of A will be translated of it
         */
        template<class TPointSet>
        void setIntersection(TPointSet &digitalIntersection,
                             const DigitalSet &A,
                             const DigitalSet &B, 
                             const Point& translation)
        {
            Point tp;
            for (auto it = A.begin(); it != A.end(); ++it)
            {
                tp = *it + translation;
                if (B(tp)) digitalIntersection.insert(tp);
            }
        }

    }
}

#endif //DIPACUS_COMPONENTS_SET_OPERATIONS_H
