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
    Point lbIn,ubIn;
    dsIn.computeBoundingBox(lbIn,ubIn);

    Point dimIn = dsIn.domain().upperBound() - dsIn.domain().lowerBound()+ Point(1,1);
    int rIn = dimIn(1);
    int cIn = dimIn(0);

    Point lbOut,ubOut;
    lbOut = dsOut.domain().lowerBound();
    ubOut = dsOut.domain().upperBound();

    Point dimOut = ubOut - lbOut + Point(1,1);
    int rOut = dimOut(1);
    int cOut = dimOut(0);


    assert(lbOut(0) <= lbIn(0) - se.size);
    assert(lbOut(1) <= lbIn(1) - se.size);

    assert(ubOut(0) >= ubIn(0) + se.size);
    assert(ubOut(1) >= ubIn(1) + se.size);


    Point shift = dsIn.domain().lowerBound();

    cv::Mat cvSrc(rOut, cOut, IMG_TYPE,cv::Scalar(0));
    cv::Mat dilation_dst(rOut, cOut, IMG_TYPE,cv::Scalar(0));

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
    Point lbIn,ubIn;
    dsIn.computeBoundingBox(lbIn,ubIn);

    Point dimIn = dsIn.domain().upperBound() - dsIn.domain().lowerBound()+ Point(1,1);
    int rIn = dimIn(1);
    int cIn = dimIn(0);

    Point lbOut,ubOut;
    lbOut = dsOut.domain().lowerBound();
    ubOut = dsOut.domain().upperBound();

    Point dimOut = ubOut - lbOut + Point(1,1);
    int rOut = dimOut(1);
    int cOut = dimOut(0);


    assert(lbOut(0) <= lbIn(0));
    assert(lbOut(1) <= lbIn(1));

    assert(ubOut(0) >= ubIn(0));
    assert(ubOut(1) >= ubIn(1));

    Point shift = dsIn.domain().lowerBound();

    cv::Mat cvSrc(rIn, cIn, IMG_TYPE, cv::Scalar(0));
    cv::Mat erosion_dst(rIn, cIn, IMG_TYPE, cv::Scalar(0));

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
