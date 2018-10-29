#ifndef DIPACUS_TESTDATA_H
#define DIPACUS_TESTDATA_H

#include <DGtal/helpers/StdDefs.h>
#include "string"

#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/shapes/GaussDigitizer.h"

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


        struct GrayscaleImageInstance
        {
            GrayscaleImageInstance(const std::string& imagePath,
                                   unsigned int totalPixels):imagePath(imagePath),
                                                             totalPixels(totalPixels){}

            const std::string imagePath;
            const unsigned int totalPixels;
        };

        namespace Data
        {
            extern GrayscaleImageInstance giSquare;
            extern DigitalSet dsSquare;
        }

    }
}

#endif //DIPACUS_TESTDATA_H
