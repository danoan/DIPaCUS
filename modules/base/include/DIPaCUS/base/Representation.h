#ifndef DIPACUS_BASE_REPRESENTATION_H
#define DIPACUS_BASE_REPRESENTATION_H

#include <DGtal/helpers/StdDefs.h>
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/kernel/sets/DigitalSetInserter.h"
#include "DGtal/io/readers/GenericReader.h"
#include "DGtal/images/ImageHelper.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

namespace DIPaCUS {
    /**
    * \brief Data representation conversions between DigitalSet and grayscale images.
     *
    * \author Daniel Martins Antunes
    * \version 0.1
    * \date 2018/08/27
    * \note Implementation is limited to grayscale images. A proposal to incorporate
    *      color images is described at
    *
    */
    namespace Representation {

        /**
         *  \brief Conversion between Image2D and DigitalSet representations
         *
         */
        struct ImageAsDigitalSet {
            typedef DGtal::Z2i::KSpace KImage;
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;

            typedef DGtal::ImageContainerBySTLVector<Domain, unsigned char> Image2D;
            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DGtal::DigitalSetInserter<DigitalSet> DigitalSetInserter;

            /**
            *  \brief Creates the DigitalSet representation of grayscale image located at imagePath.
            *  \param digitalSet DigitalSet representation output.
            *  \param imagePath Path to grayscale image.
            *  \param threshValue Pixel intensity thresholding for digital set belonginess.
            */
            ImageAsDigitalSet(DigitalSet &digitalSet,
                              const std::string imagePath,
                              int threshValue=100);


            /**
            *  \brief Creates the DigitalSet representation of grayscale image image.
            *  \param digitalSet Created DigitalSet.
            *  \param image Image2D representation of image.
            *  \param threshValue Pixel intensity thresholding for digital set belonginess.
            */
            ImageAsDigitalSet(DigitalSet &digitalSet,
                              const Image2D &image,
                              int threshValue=100);


        };

        /**
         *  \brief Conversion between DigitalSet and Image2D representations
         *
         */
        struct DigitalSetToImage {
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DGtal::Z2i::Domain Domain;

            typedef DGtal::ImageContainerBySTLVector<Domain, unsigned char> Image2D;

            /**
             * \brief Creates Image2D representation from DigitalSet representation.
             * @param img Created Image2D.
             * @param dgtalSet DigitalSet representation.
             */
            DigitalSetToImage(Image2D &img,
                              const DigitalSet &dgtalSet);
        };

        /**
         *  \brief Conversion between Image2D and cv::Mat representations
         *
         */
        struct ImageToCVMat {
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::ImageContainerBySTLVector<Domain, unsigned char> Image2D;

            /**
             * \brief Creates cv::Mat representation from Image2D representation.
             *
             * @param cvImg Created cv::Mat.
             * @param image Image2D representation.
             */
            ImageToCVMat(cv::Mat &cvImg,
                         const Image2D &image);
        };


        /**
         *  \brief Conversion between cv::Mat and Image2D representations
         *
         */
        struct CVMatToImage {
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::ImageContainerBySTLVector<Domain, unsigned char> Image2D;

            /**
             * \brief Creates Image2D representation from cv::Mat representation.
             *
             * @param image Created Image2D.
             * @param cvImg cv::Mat representation.
             */
            CVMatToImage(Image2D &image,
                         const cv::Mat &cvImg);
        };


        /**
         *  \brief Conversion between DigitalSet and cv::Mat representations
         *
         */
        struct DigitalSetToCVMat {
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::DigitalSet DigitalSet;

            /**
             * \brief Creates cv::Mat representation from DigitalSet representation.
             * @param cvImg Created cv::Mat.
             * @param dgtalSet DigitalSet representation.
             */
            DigitalSetToCVMat(cv::Mat &cvImg,
                              const DigitalSet &dgtalSet);
        };


        /**
         *  \brief Conversion between cv::Mat and DigitalSet representations
         *
         */
        struct CVMatToDigitalSet {
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DGtal::ImageContainerBySTLVector<Domain, unsigned char> Image2D;

            /**
             * \brief Creates DigitalSet representation from cv::Mat representation.
             * @param dgtalSet Created DigitalSet.
             * @param cvImg cv::Mat representation.
             * @param threshValue Pixel intensity thresholding for digital set belonginess.
             */
            CVMatToDigitalSet(DigitalSet &dgtalSet,
                              const cv::Mat &cvImg,
                              int threshValue=100,int shiftx=0, int shifty=0);
        };
    }
}

#endif //DIPACUS_BASE_REPRESENTATION_H
