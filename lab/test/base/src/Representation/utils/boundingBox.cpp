#include "Representation/utils/boundingBox.h"

using namespace Test;

void Representation::boundingBox(BoundingBox& bb,
                                 const Image2D& image)
{
    Intern::ImageAdapter imgBegin = Intern::imageAdapter(image,image.domain().begin(),1);
    Intern::ImageAdapter imgEnd = Intern::imageAdapter(image,image.domain().end(),1);

    Intern::boundingBox(bb,imgBegin,imgEnd);
}

void Representation::boundingBox(BoundingBox& bb,
                                 const cv::Mat& cvImg)
{
    Domain domain(Point(0,0),Point(cvImg.cols-1,cvImg.rows-1) );

    Intern::CVImageAdapter cvImgBegin = Intern::cvImageAdapter(cvImg,domain.begin(),1);
    Intern::CVImageAdapter cvImgEnd = Intern::cvImageAdapter(cvImg,domain.end(),1);

    Intern::boundingBox(bb,cvImgBegin,cvImgEnd);
}


using namespace Test::Representation;


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