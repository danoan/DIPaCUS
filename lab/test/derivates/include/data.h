#ifndef DIPACUS_TEST_MISC_DATA_H
#define DIPACUS_TEST_MISC_DATA_H

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/images/ImageContainerBySTLVector.h>
#include <DGtal/io/readers/GenericReader.h>

namespace DIPaCUS
{
    namespace Test
    {
        extern std::string IMAGE_INPUT_PATH;

        namespace Misc
        {
            namespace Data
            {
                typedef DGtal::ImageContainerBySTLVector<DGtal::Z2i::Domain, unsigned char> Image2D;

                extern Image2D square;
                extern Image2D squareConcavity;
                extern Image2D squareHole;
                extern Image2D squareShorts;
            }
        }
    }
}

#endif //DIPACUS_TEST_MISC_DATA_H
