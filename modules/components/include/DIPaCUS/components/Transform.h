#ifndef DIPACUS_COMPONENTS_TRANSFORM_H
#define DIPACUS_COMPONENTS_TRANSFORM_H

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/images/ImageContainerBySTLVector.h>
#include "DIPaCUS/base/Representation.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

namespace DIPaCUS
{
    /**
     * Collection of transform operations on DGtal Image, Curve and
     * DigitalSet
     *
     * \author Daniel Martins Antunes
     * \version 0.1
     * \date 2018/08/27
     */
    namespace Transform
    {
        typedef DGtal::Z2i::Point Point;
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::ImageContainerBySTLVector<Domain, unsigned char> Image2D;

        typedef DGtal::Z2i::KSpace KSpace;
        typedef DGtal::Z2i::Curve Curve;

        const int IMG_TYPE = CV_8UC1;   //Limited to grayscale images only.

        /**
         * \brief Resize a DGtal Image by a scaling factor.
         * @param out Scaled DGtal Image
         * @param input Original DGtal Image
         * @param factor Scaling factor
         */
        void resize(Image2D &out,
                    const Image2D &input,
                    double factor);


        /**
         * /brief Swap white and black pixels.
         * @param outputImage Swapped DGtal Image
         * @param inputImage Original DGtal Image
         */
        void invertColors(Image2D &outputImage,
                          const Image2D &inputImage);


        /**
         * /brief Include a border of a given width. Domain scaling
         * follows appropriately.
         *
         * @param outputImage DGtal image with border
         * @param inputImage  Original DGtal image
         * @param borderWidth Border width.
         */
        void addBorder(Image2D &outputImage,
                       const Image2D &inputImage,
                       int borderWidth);


        /**
         * /brief Eliminate loops from self-intersected curves.
         *
         * Sequentially visits the linels. If a linel is visited twice before the end
         * of the curve, remove all the linels between the first and second appearance of
         * the linel.
         * @param curveOut Curve without self loops.
         * @param KImage Khalismky Space of the given curve.
         * @param curveIn Original DGtal Curve.
         */
        void eliminateLoops(Curve &curveOut,
                            const KSpace &KImage,
                            const Curve &curveIn);


        /**
         * /brief Changes the domain of a digital set.
         *
         * The new domain has its origin set at point (0,0) and
         * dimension Length(BoundingBox(ds))+2*border. The lower
         * bounding box of original set is set at distance border
         * from origin (0,0).
         *
         * @param ds Original digital set.
         * @param border Distance of lower bounding box point of
         * original digital set from origin (0,0).
         * @return
         */
        DGtal::Z2i::DigitalSet bottomLeftBoundingBoxAtOrigin(const DGtal::Z2i::DigitalSet& ds,
                                                             const DGtal::Z2i::Point border=DGtal::Z2i::Point(10,10));

    }
}

#endif //DIPACUS_COMPONENTS_TRANSFORM_H
