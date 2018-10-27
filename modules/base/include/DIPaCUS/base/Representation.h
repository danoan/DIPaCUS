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
    * \brief Conversion between image models in DGtal and openCV libraries and
     * DGtal DigitalSets
     *
    * \author Daniel Martins Antunes
    * \version 0.1
    * \date 2018/08/27
    * \note Implementation is limited to grayscale images.
    * \note A better design might be the use of free functions
     * instead of structs.
    *
    */
    namespace Representation {

        typedef unsigned char ThresholdValue;
        typedef unsigned int ShiftValue;
        typedef DGtal::ImageContainerBySTLVector<DGtal::Z2i::Domain, unsigned char> Image2D;
        typedef DGtal::Z2i::DigitalSet DigitalSet;

        const int GRAYSCALE_IMG_TYPE = CV_8UC1;   //Limited to grayscale images only.

        /**
        *  \brief Creates the DigitalSet model of grayscale image located at imagePath.
         *
         *  Only those pixels with value greater or equal the threshold will belong to the digital
         *  set.
        *  \param dsOut DigitalSet model output.
        *  \param imgPath Path to grayscale image input.
        *  \param tv Threshold value.
        */
        void imageAsDigitalSet(DigitalSet &dsOut,
                               const std::string& imgPath,
                               const ThresholdValue tv=100);


        /**
        *  \brief Creates the DigitalSet model from DGtal grayscale image model.
         *
         *  Only those pixels with value greater or equal the threshold will belong to the digital
         *  set.
        *  \param dsOut DigitalSet model output.
        *  \param imgIn Grayscale DGtal Image model input.
        *  \param tv Threshold value.
        */
        void imageAsDigitalSet(DigitalSet &dsOut,
                               const Image2D &imgIn,
                               const ThresholdValue tv=100);



        /**
         * \brief Creates grasycale DGtal Image model from DigitalSet model.
         * @param imgOut Grayscale DGtal image model output.
         * @param dsIn DigitalSet model input.
         */
        void digitalSetToImage(Image2D &imgOut,
                               const DigitalSet &dsIn);



        /**
         * \brief Creates grayscale openCV image model from grayscale DGtal image representation.
         *
         * @param cvImgOut Grayscale openCV image model output.
         * @param imgIn Grayscale DGtal image model input.
         */
        void imageToCVMat(cv::Mat &cvImgOut,
                          const Image2D &imgIn);



        /**
         * \brief Creates grayscale DGtal image model from grayscale openCV image model.
         *
         * @param imgOut Grayscale DGtal image model output.
         * @param cvImgIn Grayscale openCV image model input.
         */
        void CVMatToImage(Image2D &imgOut,
                          const cv::Mat &cvImgIn);



        /**
         * \brief Creates grayscale openCV image model from DigitalSet model.
         * @param cvImgOut Grayscale openCV image model output.
         * @param dsIn DigitalSet model input.
         */
        void digitalSetToCVMat(cv::Mat &cvImgOut,
                               const DigitalSet &dsIn);



        /**
         * \brief Creates DigitalSet model from grayscale openCV image model.
         *
         *  Only those pixels with value greater or equal the threshold will belong to the digital
         *  set. Extra shift parameters allows to translate the points in the digital set domain.
         * @param dsOut DigitalSet model output.
         * @param cvImgIn Grayscale openCV image model input.
         * @param tv Threshold value.
         * @param sx Axis x translation.
         * @param sy Axis y translation.
         */
        void CVMatToDigitalSet(DigitalSet &dsOut,
                               const cv::Mat &cvImgIn,
                               const ThresholdValue tv=100,
                               ShiftValue sx=0,
                               ShiftValue sy=0);
    }
}

#endif //DIPACUS_BASE_REPRESENTATION_H
