#ifndef DIPACUS_COMPONENTS_BOUNDINGBOX_H
#define DIPACUS_COMPONENTS_BOUNDINGBOX_H

#include <iostream>

#include <DGtal/helpers/StdDefs.h>

namespace DIPaCUS
{
    namespace Properties
    {
        /**
         * \struct BoundingBox
         * \brief A bounding box is a data structure which represents the lower-left
         * and upper-right points of a digital set.
         *
         */
        struct BoundingBox
        {
            typedef DGtal::Z2i::Point Point;
            Point lb,ub;

            BoundingBox(){};
            BoundingBox(Point lb, Point ub):lb(lb),ub(ub){}

            inline bool operator==(const BoundingBox& other){ return other.lb == this->lb && other.ub==this->ub;}

            friend std::ostream& operator<<(std::ostream& os, const BoundingBox& bb)
            {
                os << "{ Lower left: " << bb.lb << ", " << "Upper right: " << bb.ub << std::endl;
                return os;
            }

        };

    }
}



#endif //DIPACUS_COMPONENTS_BOUNDINGBOX_H
