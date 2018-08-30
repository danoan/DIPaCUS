#include "DIPaCUS/components/Morphology.h"

using namespace DIPaCUS::Morphology;


Dilate::Dilate(Image2D &imgOut,
               const DigitalSet
               &dsIn,
               StructuringElement se,
               int size)
{
    int r = dsIn.domain().upperBound()[1] + 1;
    int c = dsIn.domain().upperBound()[0] + 1;

    cv::Mat cvSrc(r, c, IMG_TYPE);
    cv::Mat dilation_dst(r, c, IMG_TYPE);
    dilation_dst = 0;
    cvSrc = 0;

    DIPaCUS::Representation::DigitalSetToCVMat(cvSrc, dsIn);


    cv::Mat element = cv::getStructuringElement(se,
                                                cv::Size(2 * size + 1, 2 * size + 1),
                                                cv::Point(size, size));

    cv::dilate(cvSrc, dilation_dst, element);
    DIPaCUS::Representation::CVMatToImage(imgOut, dilation_dst);
}

Dilate::Dilate(DigitalSet &dgtalSetOut,
               const DigitalSet &dsIn,
               StructuringElement se,
               int size)
{
    int r = dsIn.domain().upperBound()[1] + 1;
    int c = dsIn.domain().upperBound()[0] + 1;

    cv::Mat cvSrc(r, c, IMG_TYPE);
    cv::Mat dilation_dst(r, c, IMG_TYPE);
    dilation_dst = 0;
    cvSrc = 0;

    DIPaCUS::Representation::DigitalSetToCVMat(cvSrc, dsIn);


    cv::Mat element = cv::getStructuringElement(se,
                                                cv::Size(2 * size + 1, 2 * size + 1),
                                                cv::Point(size, size));

    cv::dilate(cvSrc, dilation_dst, element);
    DIPaCUS::Representation::CVMatToDigitalSet(dgtalSetOut, dilation_dst);
}

Erode::Erode(Image2D &imgOut,
             const DigitalSet &dsIn,
             StructuringElement se,
             int size)
{
    int r = dsIn.domain().upperBound()[1] + 1;
    int c = dsIn.domain().upperBound()[0] + 1;

    cv::Mat cvSrc(r, c, IMG_TYPE);
    cv::Mat dilation_dst(r, c, IMG_TYPE);
    dilation_dst = 0;
    cvSrc = 0;

    DIPaCUS::Representation::DigitalSetToCVMat(cvSrc, dsIn);


    cv::Mat element = cv::getStructuringElement(se,
                                                cv::Size(2 * size + 1, 2 * size + 1),
                                                cv::Point(size, size));

    cv::erode(cvSrc, dilation_dst, element);
    DIPaCUS::Representation::CVMatToImage(imgOut, dilation_dst);
}

Erode::Erode(DigitalSet &dgtalSetOut,
             const DigitalSet &dsIn,
             StructuringElement se,
             int size)
{
    int r = dsIn.domain().upperBound()[1] + 1;
    int c = dsIn.domain().upperBound()[0] + 1;

    cv::Mat cvSrc(r, c, IMG_TYPE);
    cv::Mat dilation_dst(r, c, IMG_TYPE);
    dilation_dst = 0;
    cvSrc = 0;

    DIPaCUS::Representation::DigitalSetToCVMat(cvSrc, dsIn);


    cv::Mat element = cv::getStructuringElement(se,
                                                cv::Size(2 * size + 1, 2 * size + 1),
                                                cv::Point(size, size));

    cv::erode(cvSrc, dilation_dst, element);
    DIPaCUS::Representation::CVMatToDigitalSet(dgtalSetOut, dilation_dst);
}


Opening::Opening(Image2D &imgOut,
                 const DigitalSet &dsIn,
                 StructuringElement se,
                 int size)
{
    Image2D erodedImg(dsIn.domain());
    Erode(erodedImg, dsIn, se, size);
    Dilate(imgOut, dsIn, se, size);
}

Opening::Opening(DigitalSet &dgtalSetOut,
                 const DigitalSet &dsIn,
                 StructuringElement se,
                 int size)
{
    DigitalSet erodedDS(dsIn.domain());
    Erode(erodedDS,dsIn,se,size);
    Dilate(dgtalSetOut,dsIn,se,size);
}


Closing::Closing(Image2D &imgOut,
                 const DigitalSet &dsIn,
                 StructuringElement se,
                 int size)
{
    Image2D dilatedImg(dsIn.domain());
    Dilate(dilatedImg, dsIn, se, size);
    Erode(imgOut, dsIn, se, size);
}

Closing::Closing(DigitalSet &dgtalSetOut,
                 const DigitalSet &dsIn,
                 StructuringElement se,
                 int size)
{
    DigitalSet dilatedDS(dsIn.domain());
    Dilate(dilatedDS,dsIn,se,size);
    Erode(dgtalSetOut,dsIn,se,size);
}
