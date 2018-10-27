#include "DIPaCUS/base/Representation.h"

using namespace DIPaCUS;

void Representation::imageAsDigitalSet(DigitalSet &dsOut,
                       const std::string& imgPath,
                       const ThresholdValue tv)
{
    typedef DGtal::DigitalSetInserter<DigitalSet> DigitalSetInserter;
    Image2D image = DGtal::GenericReader<Image2D>::import(imgPath);

    DigitalSetInserter inserter(dsOut);
    DGtal::setFromImage(image, inserter, tv, 255);
}

void Representation::imageAsDigitalSet(DigitalSet &dsOut,
                       const Image2D &imgIn,
                       const ThresholdValue tv)
{
    typedef DGtal::DigitalSetInserter<DigitalSet> DigitalSetInserter;
    DigitalSetInserter inserter(dsOut);
    DGtal::setFromImage(imgIn, inserter, tv, 255);
}

void Representation::digitalSetToImage(Image2D &imgOut,
                       const DigitalSet &dsIn)
{
    typedef DGtal::Z2i::Point Point;
    int ubY = dsIn.domain().upperBound()[1];

    for (auto it = dsIn.begin(); it != dsIn.end(); ++it) {
        Point p = *it;
        unsigned char v = (unsigned char) (dsIn(*it)) ? 255 : 0;
        imgOut.setValue(*it,v);
    }
}




void Representation::imageToCVMat(cv::Mat &cvImgOut,
                  const Image2D &imgIn)
{
    typedef DGtal::Z2i::Point Point;
    int ubY = imgIn.domain().upperBound()[1];

    for (auto it = imgIn.domain().begin(); it != imgIn.domain().end(); ++it) {
        Point p = *it;
        unsigned char v(imgIn(*it));
        cvImgOut.at<unsigned char>((ubY - p[1]), p[0]) = v;
    }
}



void Representation::CVMatToImage(Image2D &imgOut,
                  const cv::Mat &cvImgIn)
{
    typedef DGtal::Z2i::Point Point;
    assert(cvImgIn.type()==GRAYSCALE_IMG_TYPE);

    int ubY = cvImgIn.rows - 1;
    for (int i = 0; i < cvImgIn.rows; i++) {
        for (int j = 0; j < cvImgIn.cols; j++) {
            unsigned char v(cvImgIn.at<unsigned char>(i, j));
            imgOut.setValue(Point(j, ubY - i), v);
        }
    }
}



void Representation::digitalSetToCVMat(cv::Mat &cvImgOut,
                       const DigitalSet &dsIn)
{
    typedef DGtal::Z2i::Point Point;

    cvImgOut = cv::Mat::zeros(cvImgOut.rows, cvImgOut.cols, cvImgOut.type());
    int ubY = dsIn.domain().upperBound()[1];

    for (auto it = dsIn.begin(); it != dsIn.end(); ++it) {
        Point p = *it;
        unsigned char v = (unsigned char) (dsIn(*it)) ? 255 : 0;
        cvImgOut.at<unsigned char>((ubY - p[1]), p[0]) = v;
    }
}



void Representation::CVMatToDigitalSet(DigitalSet &dsOut,
                       const cv::Mat &cvImgIn,
                       const ThresholdValue tv,
                       const ShiftValue sx,
                       const ShiftValue sy)
{
    typedef DGtal::Z2i::Point Point;
    assert(cvImgIn.type()==GRAYSCALE_IMG_TYPE);

    int ubY = cvImgIn.rows - 1;
    for (int i = 0; i < cvImgIn.rows; i++) {
        for (int j = 0; j < cvImgIn.cols; j++) {
            unsigned char v(cvImgIn.at<unsigned char>(i, j));
            if(v>tv) dsOut.insert( Point(j+sx, ubY - i + sy) );
        }
    }
}