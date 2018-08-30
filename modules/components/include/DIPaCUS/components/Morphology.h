#ifndef DIPACUS_MODULES_MORPHOLOGY_H
#define DIPACUS_MODULES_MORPHOLOGY_H

#include "DGtal/helpers/StdDefs.h"

#include "DGtal/images/ImageContainerBySTLVector.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

#include "DIPaCUS/base/Representation.h"

namespace DIPaCUS {
    namespace Morphology {
        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::ImageContainerBySTLVector<Domain, unsigned char> Image2D;

        typedef enum {
            RECT = cv::MORPH_RECT, CROSS = cv::MORPH_CROSS
        } StructuringElement;

        const int IMG_TYPE = CV_8UC1;   //Limited to grayscale images only.

        struct Dilate {

            Dilate(Image2D &imgOut,
                   const DigitalSet &dsIn,
                   StructuringElement se,
                   int size = 1);

            Dilate(DigitalSet &dgtalSetOut,
                   const DigitalSet &dsIn,
                   StructuringElement se,
                   int size = 1);

        };

        struct Erode {

            Erode(Image2D &imgOut,
                  const DigitalSet &dsIn,
                  StructuringElement se,
                  int size = 1);

            Erode(DigitalSet &dgtalSetOut,
                  const DigitalSet &dsIn,
                  StructuringElement se,
                  int size = 1);

        };

        struct Opening {

            Opening(Image2D &imgOut,
                    const DigitalSet &dsIn,
                    StructuringElement se,
                    int size = 1);

            Opening(DigitalSet &dgtalSetOut,
                    const DigitalSet &dsIn,
                    StructuringElement se,
                    int size = 1);
        };

        struct Closing {

            Closing(Image2D &imgOut,
                    const DigitalSet &dsIn,
                    StructuringElement se,
                    int size = 1);

            Closing(DigitalSet &dgtalSetOut,
                    const DigitalSet &dsIn,
                    StructuringElement se,
                    int size = 1);
        };
    }
}

#endif //DIPACUS_MODULES_MORPHOLOGY_H
