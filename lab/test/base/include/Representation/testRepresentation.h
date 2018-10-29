#ifndef TEST_DIPACUS_BASE_REPRESENTATION_H
#define TEST_DIPACUS_BASE_REPRESENTATION_H

#include <string>

#include "boost/filesystem.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include <DGtal/io/writers/GenericWriter.h>

#include "DIPaCUS/base/Representation.h"

#include "Representation/data.h"
#include <Representation/utils/boundingBox.h>

using namespace DIPaCUS::Representation;

namespace Test
{
    extern std::string IMAGE_INPUT_PATH;
    extern std::string IMAGE_OUTPUT_PATH;

    extern bool verbose;
    extern bool visualOutput;

    namespace Representation
    {
        typedef DGtal::Z2i::Point Point;
        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::ImageContainerBySTLVector<DGtal::Z2i::Domain, unsigned char> Image2D;
        typedef unsigned char ThresholdValue;

        const int GRAYSCALE_IMAGE_TYPE = CV_8UC1;

        void runTest();

        namespace Intern
        {
            void testDigitalSetToImage(const DigitalSet& tc);
            void testImageAsDigitalSet(const GrayscaleImageInstance &tc);
            void testDigitalSetToCVMat(const DigitalSet& tc);
            void testCVMatToDigitalSet(const GrayscaleImageInstance& gii);
            void testImageToCVMat(const GrayscaleImageInstance& gii);

            bool digitalPointsMapsImagePoints(const DigitalSet& ds,
                                              const cv::Mat& cvImg,
                                              const Point& translation);
        }

    };
}


#endif //TEST_DIPACUS_BASE_REPRESENTATION_H
