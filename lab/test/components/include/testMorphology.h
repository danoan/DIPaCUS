#ifndef DIPACUS_TESTMORPHOLOGY_H
#define DIPACUS_TESTMORPHOLOGY_H

#include "DIPaCUS/components/Morphology.h"

namespace Test
{
    namespace Morphology
    {
        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::Z2i::Point Point;
        typedef DGtal::Z2i::DigitalSet DigitalSet;

        bool equalBoundingBoxes(const DigitalSet& ds1, const DigitalSet& ds2);

        void testDilate(int iterations,
                        int elementSize,
                        const DigitalSet& dsInput,
                        const DigitalSet& dsCompare);

        void testErosion(int iterations,
                         int elementSize,
                         const DigitalSet& dsInput,
                         const DigitalSet& dsCompare);

        void testOpening(int iterations,
                         int elementSize,
                         const DigitalSet& dsInput);

        void testClosing(int iterations,
                         int elementSize,
                         const DigitalSet& dsInput);
    }
}

#endif //DIPACUS_TESTMORPHOLOGY_H
