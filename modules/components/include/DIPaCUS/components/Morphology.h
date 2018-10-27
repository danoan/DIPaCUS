#ifndef DIPACUS_MODULES_MORPHOLOGY_H
#define DIPACUS_MODULES_MORPHOLOGY_H

#include "DGtal/helpers/StdDefs.h"

#include "DGtal/images/ImageContainerBySTLVector.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

#include "DIPaCUS/base/Representation.h"

namespace DIPaCUS {
    /**
     * \brief Basic morpholigcal operations over DGtal DigitalSet models.
     *
     * It operates on grayscale images only.
     * \author Daniel Martins Antunes
     * \version 0.1
     * \date 2018/08/27
     */
    namespace Morphology {
        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::ImageContainerBySTLVector<Domain, unsigned char> Image2D;

        struct StructuringElement
        {
            typedef unsigned char Size;
            enum Type{RECT = cv::MORPH_RECT, CROSS = cv::MORPH_CROSS};

            StructuringElement(Type type, Size size):type(type),
                                                     size(size)
            {}

            const Type type;
            const Size size;
        } ;

        typedef unsigned int NumberIterations;
        const int IMG_TYPE = CV_8UC1;   //Limited to grayscale images only.

        /**
         * /brief Dilate DGtal digital set model and output a grayscale
         * DGtal image model.
         * @param imgOut Grayscale DGtal image model output.
         * @param dsIn DGtal digital set model input.
         * @param se Structuring element used for dilation.
         * @param it Number of dilation execution.
         */
        void dilate(Image2D &imgOut,
                    const DigitalSet &dsIn,
                    const StructuringElement se,
                    const NumberIterations it=1);

        /**
         * /brief Dilate DGtal digital set model and output a DGtal
         * digital set model.
         * @param dsOut DGtal digital set model output.
         * @param dsIn DGtal digital set model input.
         * @param se Structuring element used for dilation.
         * @param it Number of times dilation is executed.
         */
        void dilate(DigitalSet &dsOut,
                    const DigitalSet &dsIn,
                    const StructuringElement se,
                    const NumberIterations it=1);


        /**
         * /brief Erode DGtal digital set model and output a grayscale
         * DGtal image model.
         * @param imgOut Grayscale DGtal image model output.
         * @param dsIn DGtal digital set model input.
         * @param se Structuring element used for erosion.
         * @param it Number of times erosion is executed.
         */
        void erode(Image2D &imgOut,
                   const DigitalSet &dsIn,
                   const StructuringElement se,
                   const NumberIterations it=1);


        /**
         * /brief Erode DGtal digital set model and output a DGtal
         * digital set model.
         * @param dsOut DGtal digital set model output.
         * @param dsIn DGtal digital set model input.
         * @param se Structuring element used for erosion.
         * @param it Number of erosion execution.
         */
        void erode(DigitalSet &dsOut,
                   const DigitalSet &dsIn,
                   const StructuringElement se,
                   const NumberIterations iterations=1);



        /**
         * /brief Opening DGtal digital set model and output a grayscale
         * DGtal image model.
         * @param imgOut Grayscale DGtal image model output.
         * @param dsIn DGtal digital set model input.
         * @param se Structuring element used for opening.
         * @param it Number of opening execution.
         */
        void opening(Image2D &imgOut,
                     const DigitalSet &dsIn,
                     const StructuringElement se,
                     const NumberIterations it=1);


        /**
         * /brief Opening DGtal digital set model and output a DGtal
         * digital set model.
         * @param dsOut DGtal digital set model output.
         * @param dsIn DGtal digital set model input.
         * @param se Structuring element used for opening.
         * @param it Number of opening execution.
         */
        void opening(DigitalSet &dsOut,
                     const DigitalSet &dsIn,
                     const StructuringElement se,
                     const NumberIterations it=1);


        /**
         * /brief Closing DGtal digital set model and output a grayscale
         * DGtal image model.
         * @param imgOut Grayscale DGtal image model output.
         * @param dsIn DGtal digital set model input.
         * @param se Structuring element used for closing.
         * @param it Number of closing execution.
         */
        void closing(Image2D &imgOut,
                     const DigitalSet &dsIn,
                     const StructuringElement se,
                     NumberIterations it = 1);

        /**
         * /brief Closing DGtal digital set model and output a DGtal
         * digital set model.
         * @param dsOut DGtal digital set model output.
         * @param dsIn DGtal digital set model input.
         * @param se Structuring element used for closing.
         * @param it Number of closing execution.
         */
        void closing(DigitalSet &dgtalSetOut,
                     const DigitalSet &dsIn,
                     const StructuringElement se,
                     NumberIterations it = 1);
    }
}

#endif //DIPACUS_MODULES_MORPHOLOGY_H
