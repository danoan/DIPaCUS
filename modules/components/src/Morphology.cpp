#include "DIPaCUS/components/Morphology.h"

using namespace DIPaCUS;


void Morphology::dilate(Image2D &imgOut,
                        const DigitalSet &dsIn,
                        const StructuringElement se,
                        const NumberIterations it)
{
    DigitalSet dsOut(imgOut.domain());
    dilate(dsOut,dsIn,se,it);
    DIPaCUS::Representation::digitalSetToImage(imgOut,dsOut);
}

void Morphology::dilate(DigitalSet &dsOut,
                        const DigitalSet &dsIn,
                        const StructuringElement se,
                        const NumberIterations it)
{
    Point dimIn = dsIn.domain().upperBound() - dsIn.domain().lowerBound() + Point(1,1);
    int rIn = dimIn(1);
    int cIn = dimIn(0);

    Point dimOut = dsOut.domain().upperBound() - dsOut.domain().lowerBound() + Point(1,1);
    int rOut = dimOut(1);
    int cOut = dimOut(0);

    Point lbIn, ubIn;
    dsOut.computeBoundingBox(lbIn,ubIn);
    Point dimInBox = ubIn - lbIn + Point(1,1);

    assert(dimOut(0)>=dimInBox(0)+se.size);
    assert(dimOut(1)>=dimInBox(1)+se.size);


    Point shift = dsIn.domain().lowerBound();

    cv::Mat cvSrc(rIn, cIn, IMG_TYPE);
    cvSrc = 0;

    cv::Mat dilation_dst(rOut, cOut, IMG_TYPE);
    dilation_dst = 0;

    DIPaCUS::Representation::digitalSetToCVMat(cvSrc, dsIn);

    cv::Mat element = cv::getStructuringElement(se.type,
                                                cv::Size(2 * se.size +1, 2 * se.size+1 ),
                                                cv::Point(se.size,se.size)
    );


    cv::dilate(cvSrc, dilation_dst, element,cv::Point(-1,-1),it);


    DIPaCUS::Representation::CVMatToDigitalSet(dsOut, dilation_dst,1,shift(0),shift(1));
}

void Morphology::erode(Image2D &imgOut,
                       const DigitalSet &dsIn,
                       const StructuringElement se,
                       const NumberIterations it)
{
    DigitalSet dsOut(imgOut.domain());
    erode(dsOut,dsIn,se,it);
    DIPaCUS::Representation::digitalSetToImage(imgOut,dsOut);
}

void Morphology::erode(DigitalSet &dsOut,
                       const DigitalSet &dsIn,
                       const StructuringElement se,
                       const NumberIterations it)
{
    Point dimIn = dsIn.domain().upperBound() - dsIn.domain().lowerBound() + Point(1,1);
    int rIn = dimIn(1);
    int cIn = dimIn(0);

    Point dimOut = dsOut.domain().upperBound() - dsOut.domain().lowerBound() + Point(1,1);
    int rOut = dimOut(1);
    int cOut = dimOut(0);

    Point lbIn, ubIn;
    dsOut.computeBoundingBox(lbIn,ubIn);
    Point dimInBox = ubIn - lbIn + Point(1,1);

    assert(dimOut(0)>=dimInBox(0)+se.size);
    assert(dimOut(1)>=dimInBox(1)+se.size);

    Point shift = dsIn.domain().lowerBound();

    cv::Mat cvSrc(rIn, cIn, IMG_TYPE);
    cv::Mat erosion_dst(rOut, cOut, IMG_TYPE);
    erosion_dst = 0;
    cvSrc = 0;

    DIPaCUS::Representation::digitalSetToCVMat(cvSrc, dsIn);
    cv::Mat element = cv::getStructuringElement(se.type,
                                                cv::Size(2 * se.size + 1, 2 * se.size + 1),
                                                cv::Point(se.size, se.size));

    cv::erode(cvSrc, erosion_dst, element, cv::Point(-1,-1), it);
    DIPaCUS::Representation::CVMatToDigitalSet(dsOut, erosion_dst, 1, shift(0), shift(1) );
}


void Morphology::opening(Image2D &imgOut,
                         const DigitalSet &dsIn,
                         const StructuringElement se,
                         const NumberIterations it)
{
    DigitalSet dsOut(imgOut.domain());
    opening(dsOut,dsIn,se,it);

    DIPaCUS::Representation::digitalSetToImage(imgOut,dsOut);
}

void Morphology::opening(DigitalSet &dsOut,
                         const DigitalSet &dsIn,
                         const StructuringElement se,
                         const NumberIterations it)
{
    DigitalSet partialEroded(dsOut.domain());
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
    DigitalSet dsOut(imgOut.domain());

    closing(dsOut,dsIn,se,it);
    DIPaCUS::Representation::digitalSetToImage(imgOut,dsOut);
}

void Morphology::closing(DigitalSet &dsOut,
                         const DigitalSet &dsIn,
                         const StructuringElement se,
                         const NumberIterations it)
{
    DigitalSet partialDilated(dsOut.domain());
    dsOut = dsIn;
    for(int i=0;i<it;++i)
    {
        partialDilated.clear();
        dilate(partialDilated,dsOut,se);

        dsOut.clear();
        erode(dsOut,partialDilated,se);
    }
}
