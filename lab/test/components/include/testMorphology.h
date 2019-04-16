#ifndef DIPACUS_TEST_COMPONENTS_MORPHOLOGY_H
#define DIPACUS_TEST_COMPONENTS_MORPHOLOGY_H

#include "DIPaCUS/components/Morphology.h"
#include "logger/logger.h"

namespace DIPaCUS
{
    namespace Test
    {
        namespace Morphology
        {
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::DigitalSet DigitalSet;

            bool equalBoundingBoxes(const DigitalSet& ds1, const DigitalSet& ds2);

            bool testDilate(int iterations,
                            int elementSize,
                            const DigitalSet& dsInput,
                            const DigitalSet& dsCompare,
                            Logger& logger);

            bool testErosion(int iterations,
                             int elementSize,
                             const DigitalSet& dsInput,
                             const DigitalSet& dsCompare,
                             Logger& logger);

            bool testOpening(int iterations,
                             int elementSize,
                             const DigitalSet& dsInput,
                             Logger& logger);

            bool testClosing(int iterations,
                             int elementSize,
                             const DigitalSet& dsInput,
                             Logger& logger);

            bool runTest(std::ostream& os, const std::string& outputFolder, bool exportObjects=false);
        }
    }
}

#endif //DIPACUS_TEST_COMPONENTS_MORPHOLOGY_H
