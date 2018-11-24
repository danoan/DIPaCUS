#ifndef DIPACUS_TEST_UTILS_H
#define DIPACUS_TEST_UTILS_H

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/boards/Board2D.h>

#include <DGtal/shapes/parametric/NGon2D.h>
#include <DGtal/shapes/GaussDigitizer.h>

#include <DGtal/images/SimpleThresholdForegroundPredicate.h>

#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/base/Representation.h>

#include "boundingBox.h"

namespace Test
{
    namespace Utils
    {
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::Z2i::Space Space;
        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::Z2i::Curve Curve;


        DigitalSet createSquareDS(int sideLength);

        void boundingBox(BoundingBox& bb,
                         const Image2D& image);

        void boundingBox(BoundingBox& bb,
                         const cv::Mat& cvImg);

        void computeBoundaryCurve(const DigitalSet& ds,
                                  Curve& boundCurve);
    }
}

#endif //DIPACUS_TEST_UTILS_H
