#include "DIPaCUS/components/intern/properties/boundingBox/adapter.h"

namespace DIPaCUS{ namespace Properties{

    Intern::ImageAdapter Intern::imageAdapter(const Image2D& imgIn,
                                              const Domain::ConstIterator dIt,
                                              const ThresholdValue& tv)
    {
        ImageDomainAdapterFn myAdapter= [imgIn,tv](Point p){ return PointFilter(p,imgIn(p)>tv);};
        ImageAdapter imageAdapter(dIt,myAdapter);

        return imageAdapter;
    }

    Intern::CVImageAdapter Intern::cvImageAdapter(const cv::Mat& cvImgIn,
                                                  const Domain::ConstIterator dIt,
                                                  const ThresholdValue& tv)
    {
        const int rows =  cvImgIn.rows-1;
        CVImageAdapterFn myAdapter = [cvImgIn,tv,rows](Point p){ return PointFilter(p,cvImgIn.at<unsigned char>(rows-p(1),p(0))>tv); };
        CVImageAdapter cvAdapter(dIt,myAdapter);
        return cvAdapter;
    }
}}