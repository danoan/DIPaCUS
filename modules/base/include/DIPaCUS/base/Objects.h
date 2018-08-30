#ifndef DIPACUS_BASE_OBJECTS_H
#define DIPACUS_BASE_OBJECTS_H


#include <DGtal/helpers/StdDefs.h>

namespace DIPaCUS
{
    namespace Objects
    {
        class DigitalRectangle {
        public:
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::Domain Domain;

            typedef DGtal::Z2i::DigitalSet DigitalSet;

        public:
            DigitalRectangle(DigitalSet &dsRect,
                             Domain domain,
                             Point bottomLeftCorner,
                             unsigned int s1,
                             unsigned int s2);
        };
    }
}

#endif //DIPACUS_BASE_OBJECTS_H
