#ifndef TEST_DIPACUS_BASE_REPRESENTATION_H
#define TEST_DIPACUS_BASE_REPRESENTATION_H

#include <string>

#include <boost/filesystem.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <DGtal/io/writers/GenericWriter.h>

#include "DIPaCUS/base/Representation.h"
#include "DIPaCUS/components/auxiliar/properties/boundingBox.h"

#include "Representation/data.h"
#include "logger/logger.h"


namespace DIPaCUS
{
    namespace Test
    {
        extern std::string IMAGE_INPUT_PATH;

        namespace Representation
        {
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::ImageContainerBySTLVector<DGtal::Z2i::Domain, unsigned char> Image2D;
            typedef unsigned char ThresholdValue;
            typedef DIPaCUS::Properties::BoundingBox BoundingBox;

            const int GRAYSCALE_IMAGE_TYPE = CV_8UC1;

            namespace Intern
            {
                void boundingBox(BoundingBox& bb, const Image2D& img);
                void boundingBox(BoundingBox& bb, const cv::Mat& cvImg);

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

            bool testDigitalSetToImage(const DigitalSet& tc,Logger& logger);
            bool testImageAsDigitalSet(const std::string &tc,Logger& logger);
            bool testDigitalSetToCVMat(const DigitalSet& tc,Logger& logger);
            bool testCVMatToDigitalSet(const std::string& gii,Logger& logger);
            bool testImageToCVMat(const std::string& gii,Logger& logger);

            bool runTest(std::ostream& os, std::string outputFolder, bool exportObjectsFlag=false);


        };
    }
}

#endif //TEST_DIPACUS_BASE_REPRESENTATION_H
