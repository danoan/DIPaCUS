#ifndef DIPACUS_COMPONENTS_PROPERTIES_H
#define DIPACUS_COMPONENTS_PROPERTIES_H

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/components/properties/boundingBox.h>

namespace DIPaCUS
{
    /**
    * \brief Collection of property gathering functions.
    * \author Daniel Martins Antunes
    * \version 0.1
    * \date 2018/08/27
    */
    namespace Properties
    {
        typedef DGtal::Z2i::Point Point;

        /**
         * \brief Computes the bounding box of a curve.
         *
         * Bounding Box is given in terms of incident pixel coordinates
         * (recall that SCells lies in Khalimsky Space).
         *
         * @tparam TSCellIterator It must be an iterator on DGtal SCells
         * @param bb BoundingBox struct
         * @param itb Begin iterator
         * @param ite End iterator
         */
        template<class TSCellIterator>
        void curveBoundingBox(BoundingBox& bb, TSCellIterator itb, TSCellIterator ite);


        /**
         * \brief Computes bounding box of a Grayscale DGtal Image.
         *
         * Any pixel with intensity value higher than 1 is taken
         * into account for bounding box computation
         *
         * @param bb BoundingBox
         * @param image DGtal Image
         */
        void boundingBox(BoundingBox& bb,
                         const Image2D& image);

        /**
         * \brief Computes bounding box of a Grayscale openCV Image.
         *
         * Any pixel with intensity value higher than 1 is taken
         * into account for bounding box computation
         *
         * @param bb BoundingBox
         * @param cvImg openCV Image
         */
        void boundingBox(BoundingBox& bb,
                         const cv::Mat& cvImg);
    }

}

#include "Properties.hpp"

#endif //DIPACUS_COMPONENTS_PROPERTIES_H
