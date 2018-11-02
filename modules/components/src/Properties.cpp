#include "DIPaCUS/components/Properties.h"

using namespace DIPaCUS;

void Properties::boundingBox(BoundingBox& bb,
                             const Image2D& image)
{
    Intern::ImageAdapter imgBegin = Intern::imageAdapter(image,image.domain().begin(),1);
    Intern::ImageAdapter imgEnd = Intern::imageAdapter(image,image.domain().end(),1);

    Intern::boundingBox(bb,imgBegin,imgEnd);
}

void Properties::boundingBox(BoundingBox& bb,
                             const cv::Mat& cvImg)
{
    Domain domain(Point(0,0),Point(cvImg.cols-1,cvImg.rows-1) );

    Intern::CVImageAdapter cvImgBegin = Intern::cvImageAdapter(cvImg,domain.begin(),1);
    Intern::CVImageAdapter cvImgEnd = Intern::cvImageAdapter(cvImg,domain.end(),1);

    Intern::boundingBox(bb,cvImgBegin,cvImgEnd);
}

