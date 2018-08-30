#ifndef DIPACUS_MODULES_SET_OPERATIONS_H
#define DIPACUS_MODULES_SET_OPERATIONS_H


#include <DGtal/helpers/StdDefs.h>
#include "DGtal/kernel/sets/DigitalSetInserter.h"

namespace DIPaCUS {
    namespace SetOperations {
        struct SetDifference {
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;

            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DGtal::DigitalSetInserter<DigitalSet> DigitalSetInserter;

            SetDifference(DigitalSet &differenceSet,
                          const DigitalSet &A,
                          const DigitalSet &B);
        };

        struct SetIntersection {
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::DigitalSet DigitalSet;

            SetIntersection(DigitalSet &digitalIntersection,
                            const DigitalSet &A,
                            const DigitalSet &B);
        };
    }
}

#endif //DIPACUS_MODULES_SET_OPERATIONS_H
