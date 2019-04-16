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
        void setIntersection(DigitalSet &digitalIntersection,
                             const DigitalSet &A,
                             const DigitalSet &B);
    }
}

#endif //DIPACUS_COMPONENTS_SET_OPERATIONS_H
