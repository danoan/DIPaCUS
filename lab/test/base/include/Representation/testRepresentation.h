#ifndef TEST_DIPACUS_BASE_REPRESENTATION_H
#define TEST_DIPACUS_BASE_REPRESENTATION_H

#include <string>

#include "boost/filesystem.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include <DGtal/io/writers/GenericWriter.h>

#include "DIPaCUS/base/Representation.h"

#include "Representation/data.h"
#include "utils/utils.h"

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
            typedef Test::Utils::BoundingBox BoundingBox;

            void testDigitalSetToImage(const DigitalSet& tc);
            void testImageAsDigitalSet(const std::string &tc);
            void testDigitalSetToCVMat(const DigitalSet& tc);
            void testCVMatToDigitalSet(const std::string& gii);
            void testImageToCVMat(const std::string& gii);


            /**
             * \brief Checks if digital set points map to non-zero image pixel and likewise,
             * if domain points but not part of the set maps to zero image pixel.
             *
             * @param ds DigitalSet to test
             * @param cvImg Grayscale openCV image map candidate
             * @param translation Translation map between DigitalSet and grayscale openCV Image.
             * @return The digital set is correctly mapped to the image.
             */
            bool digitalPointsMapsImagePoints(const DigitalSet& ds,
                                              const cv::Mat& cvImg,
                                              const Point& translation);



            /**
             * \brief Checks if digital set points map to non-zero image pixel and likewise,
             * if domain points but not part of the set maps to zero image pixel.
             *
             * @param ds DigitalSet to test
             * @param image Grayscale DGtal image map candidate
             * @param translation Translation map between DigitalSet and grayscale DGtal Image.
             * @return The digital set is correctly mapped to the image.
             */
            bool digitalPointsMapsImagePoints(const DigitalSet& ds,
                                              const Image2D& image,
                                              const Point& translation);
        }

    };
}


#endif //TEST_DIPACUS_BASE_REPRESENTATION_H
