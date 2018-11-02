#ifndef DIPACUS_TEST_BASE_REPRESENTATION_BOUNDINGBOX_H
#define DIPACUS_TEST_BASE_REPRESENTATION_BOUNDINGBOX_H

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/images/ImageContainerBySTLVector.h>
#include <opencv2/core/mat.hpp>

namespace Test
{
    namespace Utils
    {
        typedef DGtal::Z2i::Point Point;
        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::ImageContainerBySTLVector<DGtal::Z2i::Domain, unsigned char> Image2D;
        typedef unsigned char ThresholdValue;

        struct BoundingBox
        {
            typedef DGtal::Z2i::Point Point;
            Point lb,ub;

            inline bool operator==(const BoundingBox& other){ return other.lb == this->lb && other.ub==this->ub;}
        };



        namespace Intern
        {
            struct PointFilter
            {
                PointFilter(const Point& point,
                            bool valid):point(point),
                                        valid(valid){}

                const Point point;
                const bool valid;
            };

            typedef DGtal::Z2i::Domain::ConstIterator DomainIterator;
            typedef std::function<PointFilter(Point)> ImageDomainAdapterFn;
            typedef DGtal::ConstIteratorAdapter<DomainIterator,ImageDomainAdapterFn,PointFilter> ImageAdapter;

            typedef std::function<PointFilter(Point)> CVImageAdapterFn;
            typedef DGtal::ConstIteratorAdapter<DomainIterator,CVImageAdapterFn,PointFilter> CVImageAdapter;

            template<typename TPointFilterIterator>
            void boundingBox(BoundingBox& bb, TPointFilterIterator itb, TPointFilterIterator ite);


            ImageAdapter imageAdapter(const Image2D& image,
                                      const Domain::ConstIterator dIt,
                                      const ThresholdValue& tv);

            CVImageAdapter cvImageAdapter(const cv::Mat& cvImg,
                                          const Domain::ConstIterator dIt,
                                          const ThresholdValue& tv);
        }
    }
}

#include "boundingBox.hpp"

#endif //DIPACUS_TEST_BASE_REPRESENTATION_BOUNDINGBOX_H
