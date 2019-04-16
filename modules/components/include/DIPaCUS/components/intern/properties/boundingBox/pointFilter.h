#ifndef DIPACUS_COMPONENTS_INTERN_POINTFILTER_H
#define DIPACUS_COMPONENTS_INTERN_POINTFILTER_H

#include <DGtal/helpers/StdDefs.h>

namespace DIPaCUS
{
    namespace Properties
    {
        namespace Intern
        {
            struct PointFilter
            {
                typedef DGtal::Z2i::Point Point;

                PointFilter(const Point& point,
                            bool valid):point(point),
                                        valid(valid){}

                const Point point;
                const bool valid;
            };

        }
    }
}

#endif //DIPACUS_COMPONENTS_INTERN_POINTFILTER_H
