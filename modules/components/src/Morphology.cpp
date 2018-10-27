#include "DIPaCUS/components/Morphology.h"

using namespace DIPaCUS;


void Morphology::dilate(Image2D &imgOut,
                        const DigitalSet &dsIn,
                        const StructuringElement se,
                        const NumberIterations it)
{
    int r = dsIn.domain().upperBound()[1] + 1;
    int c = dsIn.domain().upperBound()[0] + 1;

    cv::Mat cvSrc(r, c, IMG_TYPE);
    cv::Mat dilation_dst(r, c, IMG_TYPE);
    dilation_dst = 0;
    cvSrc = 0;

    DIPaCUS::Representation::digitalSetToCVMat(cvSrc, dsIn);


    cv::Mat element = cv::getStructuringElement(se.type,
                                                cv::Size(2 * se.size + 1, 2 * se.size + 1),
                                                cv::Point(se.size, se.size));

    cv::dilate(cvSrc, dilation_dst, element,cv::Point(-1,-1),it);
    DIPaCUS::Representation::CVMatToImage(imgOut, dilation_dst);
}

void Morphology::dilate(DigitalSet &dsOut,
                        const DigitalSet &dsIn,
                        const StructuringElement se,
                        const NumberIterations it)
{
    int r = dsIn.domain().upperBound()[1] + 1;
    int c = dsIn.domain().upperBound()[0] + 1;

    cv::Mat cvSrc(r, c, IMG_TYPE);
    cvSrc = 0;

    cv::Mat dilation_dst(r, c, IMG_TYPE);
    dilation_dst = 0;

    DIPaCUS::Representation::digitalSetToCVMat(cvSrc, dsIn);

    cv::Mat element = cv::getStructuringElement(se.type,
                                                cv::Size(2 * se.size +1, 2 * se.size+1 ),
                                                cv::Point(se.size,se.size)
    );

    cv::dilate(cvSrc, dilation_dst, element,cv::Point(-1,-1),it);
    DIPaCUS::Representation::CVMatToDigitalSet(dsOut, dilation_dst);
}

void Morphology::erode(Image2D &imgOut,
                       const DigitalSet &dsIn,
                       const StructuringElement se,
                       const NumberIterations it)
{
    int r = dsIn.domain().upperBound()[1] + 1;
    int c = dsIn.domain().upperBound()[0] + 1;

    cv::Mat cvSrc(r, c, IMG_TYPE);
    cv::Mat dilation_dst(r, c, IMG_TYPE);
    dilation_dst = 0;
    cvSrc = 0;

    DIPaCUS::Representation::digitalSetToCVMat(cvSrc, dsIn);


    cv::Mat element = cv::getStructuringElement(se.type,
                                                cv::Size(2 * se.size + 1, 2 * se.size + 1),
                                                cv::Point(se.size, se.size));

    cv::erode(cvSrc, dilation_dst, element, cv::Point(-1,-1),it);
    DIPaCUS::Representation::CVMatToImage(imgOut, dilation_dst);
}

void Morphology::erode(DigitalSet &dsOut,
                       const DigitalSet &dsIn,
                       const StructuringElement se,
                       const NumberIterations it)
{
    int r = dsIn.domain().upperBound()[1] + 1;
    int c = dsIn.domain().upperBound()[0] + 1;

    cv::Mat cvSrc(r, c, IMG_TYPE);
    cv::Mat dilation_dst(r, c, IMG_TYPE);
    dilation_dst = 0;
    cvSrc = 0;

    DIPaCUS::Representation::digitalSetToCVMat(cvSrc, dsIn);
    cv::Mat element = cv::getStructuringElement(se.type,
                                                cv::Size(2 * se.size + 1, 2 * se.size + 1),
                                                cv::Point(se.size, se.size));

    cv::erode(cvSrc, dilation_dst, element, cv::Point(-1,-1), it);
    DIPaCUS::Representation::CVMatToDigitalSet(dsOut, dilation_dst);
}


void Morphology::opening(Image2D &imgOut,
                         const DigitalSet &dsIn,
                         const StructuringElement se,
                         const NumberIterations it)
{
    DigitalSet dsOut(dsIn.domain());
    opening(dsOut,dsIn,se,it);

    DIPaCUS::Representation::digitalSetToImage(imgOut,dsOut);
}

void Morphology::opening(DigitalSet &dsOut,
                         const DigitalSet &dsIn,
                         const StructuringElement se,
                         const NumberIterations it)
{
    DigitalSet partialEroded(dsIn.domain());
    dsOut = dsIn;
    for(int i=0;i<it;++i)
    {
        partialEroded.clear();
        erode(partialEroded, dsOut, se);

        dsOut.clear();
        dilate(dsOut, partialEroded, se);
    }
}


void Morphology::closing(Image2D &imgOut,
                         const DigitalSet &dsIn,
                         const StructuringElement se,
                         const NumberIterations it)
{
    DigitalSet dsOut(dsIn.domain());

    closing(dsOut,dsIn,se,it);
    DIPaCUS::Representation::digitalSetToImage(imgOut,dsOut);
}

void Morphology::closing(DigitalSet &dsOut,
                         const DigitalSet &dsIn,
                         const StructuringElement se,
                         const NumberIterations it)
{
    DigitalSet partialDilated(dsIn.domain());
    dsOut = dsIn;
    for(int i=0;i<it;++i)
    {
        partialDilated.clear();
        dilate(partialDilated,dsOut,se);

        dsOut.clear();
        erode(dsOut,partialDilated,se);
    }
}
