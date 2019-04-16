#include "DIPaCUS/components/Properties.h"

using namespace DIPaCUS;

void Properties::boundingBox(BoundingBox& bb,
                             const Image2D& imgIn)
{
    Intern::ImageAdapter imgBegin = Intern::imageAdapter(imgIn,imgIn.domain().begin(),1);
    Intern::ImageAdapter imgEnd = Intern::imageAdapter(imgIn,imgIn.domain().end(),1);

    Intern::boundingBox(bb,imgBegin,imgEnd);
}

void Properties::boundingBox(BoundingBox& bb,
                             const cv::Mat& cvImgIn)
{
    typedef BoundingBox::Point Point;

    DGtal::Z2i::Domain domain(Point(0,0),Point(cvImgIn.cols-1,cvImgIn.rows-1) );

    Intern::CVImageAdapter cvImgBegin = Intern::cvImageAdapter(cvImgIn,domain.begin(),1);
    Intern::CVImageAdapter cvImgEnd = Intern::cvImageAdapter(cvImgIn,domain.end(),1);

    Intern::boundingBox(bb,cvImgBegin,cvImgEnd);
}

