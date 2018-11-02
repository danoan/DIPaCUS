#include "utils/utils.h"

using namespace Test;

Utils::DigitalSet Utils::createSquareDS(int sideLength)
{
    double radius = sideLength/2.0*sqrt(2);

    NGon2D square(0,0,radius,4,3.1416/4.0);
    DGtal::GaussDigitizer<Space,NGon2D> gd;
    gd.attach(square);
    gd.init(square.getLowerBound(),square.getUpperBound(),1.0);

    Domain squareDomain = Domain( square.getLowerBound(),square.getUpperBound() );
    DigitalSet squareDS( squareDomain );
    for(auto it=squareDomain.begin();it!=squareDomain.end();++it)
    {
        if(gd.operator()(*it)) squareDS.insert(*it);
    }

    DGtal::Board2D board;
    board << squareDS;
    board.saveEPS("ds.eps");

    return squareDS;
}

void Utils::boundingBox(BoundingBox& bb,
                                 const Image2D& image)
{
    Intern::ImageAdapter imgBegin = Intern::imageAdapter(image,image.domain().begin(),1);
    Intern::ImageAdapter imgEnd = Intern::imageAdapter(image,image.domain().end(),1);

    Intern::boundingBox(bb,imgBegin,imgEnd);
}

void Utils::boundingBox(BoundingBox& bb,
                                 const cv::Mat& cvImg)
{
    Domain domain(Point(0,0),Point(cvImg.cols-1,cvImg.rows-1) );

    Intern::CVImageAdapter cvImgBegin = Intern::cvImageAdapter(cvImg,domain.begin(),1);
    Intern::CVImageAdapter cvImgEnd = Intern::cvImageAdapter(cvImg,domain.end(),1);

    Intern::boundingBox(bb,cvImgBegin,cvImgEnd);
}