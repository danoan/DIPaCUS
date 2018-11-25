#ifndef DIPACUS_TESTTRANSFORM_H
#define DIPACUS_TESTTRANSFORM_H

#include <DGtal/helpers/StdDefs.h>

#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/components/Transform.h>

namespace Test
{
    namespace Transform
    {
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::Z2i::Point Point;
        typedef DIPaCUS::Representation::Image2D Image2D;

        void testResize();
        void testInvertColors();
        void testAddBorder();

        void testExecution();
    }
}

#endif //DIPACUS_TESTTRANSFORM_H
