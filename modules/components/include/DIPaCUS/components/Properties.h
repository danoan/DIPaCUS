#ifndef DIPACUS_PROPERTIES_H
#define DIPACUS_PROPERTIES_H

#include <DGtal/helpers/StdDefs.h>

namespace DIPaCUS
{
    namespace Properties
    {
        template<class TSCellIterator>
        struct CurveBoundingBox
        {
            typedef DGtal::Z2i::Point Point;

            struct BoundingBox
            {
                Point lb,ub;
            };

            CurveBoundingBox(BoundingBox& bb, TSCellIterator itb, TSCellIterator ite);
        };
    }

#include "Properties.hpp"
}

#endif //DIPACUS_PROPERTIES_H
