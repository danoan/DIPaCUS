#ifndef DIPACUS_TEST_BASE_REPRESENTATION_DATA_H
#define DIPACUS_TEST_BASE_REPRESENTATION_DATA_H

#include <string>

#include <DGtal/helpers/StdDefs.h>

#include <DGtal/shapes/ShapeFactory.h>
#include <DGtal/shapes/GaussDigitizer.h>

#include "DIPaCUS/base/Shapes.h"

namespace DIPaCUS
{
    namespace Test
    {
        extern std::string IMAGE_INPUT_PATH;

        namespace Representation
        {
            typedef DGtal::Z2i::DigitalSet DigitalSet;

            namespace Intern
            {
                typedef DGtal::Z2i::Space Space;
                typedef DGtal::Z2i::Domain Domain;
                typedef DGtal::NGon2D<Space> NGon2D;

                DigitalSet createSquareDS();
            }


            namespace Data
            {
                extern std::string giSquare;
                extern DigitalSet dsSquare;
            }

        }
    }
}
#endif //DIPACUS_TEST_BASE_REPRESENTATION_DATA_H
