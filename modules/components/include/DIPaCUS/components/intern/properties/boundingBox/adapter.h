#ifndef DIPACUS_COMPONENTS_INTERN_ADAPTER_H
#define DIPACUS_COMPONENTS_INTERN_ADAPTER_H

#include <opencv2/core/mat.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/images/ImageContainerBySTLVector.h>

#include "DIPaCUS/components/intern/properties/boundingBox/pointFilter.h"
#include "DIPaCUS/components/auxiliar/properties/boundingBox.h"

namespace DIPaCUS
{
    namespace Properties
    {
        namespace Intern
        {
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::ImageContainerBySTLVector<DGtal::Z2i::Domain, unsigned char> Image2D;
            typedef unsigned char ThresholdValue;


            typedef Domain::ConstIterator DomainIterator;
            typedef std::function<PointFilter(Point)> ImageDomainAdapterFn;
            typedef DGtal::ConstIteratorAdapter<DomainIterator,ImageDomainAdapterFn,PointFilter> ImageAdapter;

            typedef std::function<PointFilter(Point)> CVImageAdapterFn;
            typedef DGtal::ConstIteratorAdapter<DomainIterator,CVImageAdapterFn,PointFilter> CVImageAdapter;


            /**
             * \brief Creates adapter for Image2D types in order to compute its
             * bounding box.
             *
             * This function is used internally by
             * boundingBox(BoundingBox&, TPointFilterIterator, TPointFilterIterator)
             * @param imgIn Grayscale DGtal Image model input.
             * @param dIt Image domain iterator
             * @param tv Only pixels in which intensity is above the threshold value
             * are considered in the computation
             * @return ImageAdapter
             */
            ImageAdapter imageAdapter(const Image2D& imgIn,
                                      const Domain::ConstIterator dIt,
                                      const ThresholdValue& tv);

            /**
             * \brief Creates adapter for openCV type images in order to compute its
             * bounding box.
             *
             * This function is used internally by
             * boundingBox(BoundingBox&, TPointFilterIterator, TPointFilterIterator)
             * @param cvImgIn Grayscale openCV image model input.
             * @param dIt openCV image domain iterator
             * @param tv Only pixels in which intensity is above the threshold value
             * are considered in the computation
             * @return CVImageAdapter
             */
            CVImageAdapter cvImageAdapter(const cv::Mat& cvImgIn,
                                          const Domain::ConstIterator dIt,
                                          const ThresholdValue& tv);

            template<typename TPointFilterIterator>
            void boundingBox(BoundingBox& bb, TPointFilterIterator itb, TPointFilterIterator ite);
        }
    }
}

#include "DIPaCUS/components/intern/properties/boundingBox/adapter.hpp"

#endif //DIPACUS_COMPONENTS_INTERN_ADAPTER_H
