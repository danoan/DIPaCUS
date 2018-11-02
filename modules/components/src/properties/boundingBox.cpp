#include "DIPaCUS/components/properties/boundingBox.h"

namespace DIPaCUS{ namespace Properties{

    Intern::ImageAdapter Intern::imageAdapter(const Image2D& image,
                                              const Domain::ConstIterator dIt,
                                              const ThresholdValue& tv)
    {
        ImageDomainAdapterFn myAdapter= [image,tv](Point p){ return PointFilter(p,image(p)>tv);};
        ImageAdapter imageAdapter(dIt,myAdapter);

        return imageAdapter;
    }

    Intern::CVImageAdapter Intern::cvImageAdapter(const cv::Mat& cvImg,
                                                  const Domain::ConstIterator dIt,
                                                  const ThresholdValue& tv)
    {
        const int rows =  cvImg.rows-1;
        CVImageAdapterFn myAdapter = [cvImg,tv,rows](Point p){ return PointFilter(p,cvImg.at<unsigned char>(rows-p(1),p(0))>tv); };
        CVImageAdapter cvAdapter(dIt,myAdapter);
        return cvAdapter;
    }
}}