#include "DIPaCUS/base/Representation.h"

using namespace DIPaCUS::Representation;

ImageAsDigitalSet::ImageAsDigitalSet(DigitalSet &digitalSet,
                                     const std::string imagePath,
                                     int threshValue)
{
    Image2D image = DGtal::GenericReader<Image2D>::import(imagePath);

    DigitalSetInserter inserter(digitalSet);
    DGtal::setFromImage(image, inserter, threshValue, 255);
}

ImageAsDigitalSet::ImageAsDigitalSet(DigitalSet &digitalSet,
                                     const Image2D &image,
                                     int threshValue)
{
    DigitalSetInserter inserter(digitalSet);
    DGtal::setFromImage(image, inserter, threshValue, 255);
}



ImageToCVMat::ImageToCVMat(cv::Mat &cvImg,
                           const Image2D &dgtalImg)
{
    int ubY = dgtalImg.domain().upperBound()[1];

    for (auto it = dgtalImg.domain().begin(); it != dgtalImg.domain().end(); ++it) {
        Point p = *it;
        unsigned char v(dgtalImg(*it));
        cvImg.at<unsigned char>((ubY - p[1]), p[0]) = v;
    }
}



CVMatToImage::CVMatToImage(Image2D &dgtalImg,
                           const cv::Mat &cvImg)
{
    int ubY = cvImg.rows - 1;
    for (int i = 0; i < cvImg.rows; i++) {
        for (int j = 0; j < cvImg.cols; j++) {
            unsigned char v(cvImg.at<unsigned char>(i, j));
            dgtalImg.setValue(Point(j, ubY - i), v);
        }
    }
}



DigitalSetToCVMat::DigitalSetToCVMat(cv::Mat &cvImg,
                                     const DigitalSet &dgtalSet)
{
    cvImg = cvImg.zeros(cvImg.rows, cvImg.cols, cvImg.type());
    int ubY = dgtalSet.domain().upperBound()[1] - 1;

    for (auto it = dgtalSet.begin(); it != dgtalSet.end(); ++it) {
        Point p = *it;
        unsigned char v = (unsigned char) (dgtalSet(*it)) ? 255 : 0;
        cvImg.at<unsigned char>((ubY - p[1]), p[0]) = v;
    }
}



CVMatToDigitalSet::CVMatToDigitalSet(DigitalSet &dgtalSet,
                                     const cv::Mat &cvImg,
                                     int threshValue)
{
    Domain domain(Point(0, 0), Point(cvImg.cols - 1, cvImg.rows - 1));

    Image2D temp(domain);
    int ubY = cvImg.rows - 1;
    for (int i = 0; i < cvImg.rows; i++) {
        for (int j = 0; j < cvImg.cols; j++) {
            unsigned char v(cvImg.at<unsigned char>(i, j));
            temp.setValue(Point(j, ubY - i), v);
        }
    }
    ImageAsDigitalSet(dgtalSet, temp, threshValue);
}