#ifndef DIPACUS_MODULES__TRANSFORM_H
#define DIPACUS_MODULES__TRANSFORM_H

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/images/ImageContainerBySTLVector.h>
#include "DIPaCUS/base/Representation.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

namespace DIPaCUS
{
    namespace Transform {
        struct Resize {
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::ImageContainerBySTLVector<Domain, unsigned char> Image2D;

            const int IMG_TYPE = CV_8UC1;   //Limited to grayscale images only.

            Resize(Image2D &input,
                   Image2D &out,
                   double factor);
        };

        struct InvertColors {
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::ImageContainerBySTLVector<Domain, unsigned char> Image2D;

            const int IMG_TYPE = CV_8UC1;   //Limited to grayscale images only.

            InvertColors(Image2D &outputImage,
                         Image2D &inputImage);
        };

        struct AddBorder {
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::ImageContainerBySTLVector<Domain, unsigned char> Image2D;

            const int IMG_TYPE = CV_8UC1;   //Limited to grayscale images only.

            AddBorder(Image2D &outputImage,
                      Image2D &inputImage,
                      int borderWidth);
        };

        struct EliminateLoops {
            typedef DGtal::Z2i::KSpace KSpace;
            typedef DGtal::Z2i::Curve Curve;


            /*
             * Eliminate loops from self intersected curves.
             *
             * Description: The curve is
             */
            EliminateLoops(Curve &curveOut,
                           KSpace &KImage,
                           Curve &curveIn);
        };
        
        static DGtal::Z2i::DigitalSet CenterDigitalSetAtOrigin(const DGtal::Z2i::DigitalSet& ds);

    }
}

#endif //DIPACUS_MODULES_TRANSFORM_H
