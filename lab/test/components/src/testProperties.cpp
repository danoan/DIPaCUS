#include <DIPaCUS/components/Properties.h>
#include <DIPaCUS/base/Shapes.h>
#include <utils/utils.h>
#include "testProperties.h"

namespace Test{ namespace Properties{

    void testExecution()
    {
        DIPaCUS::Properties::BoundingBox bbSquare, bbImage, bbOCV;

        DigitalSet square = DIPaCUS::Shapes::square();
        DGtal::Z2i::Curve curve;

        Utils::computeBoundaryCurve(square,curve);
        DIPaCUS::Properties::curveBoundingBox(bbSquare,curve.begin(),curve.end());

        DIPaCUS::Representation::Image2D squareImage(square.domain());
        DIPaCUS::Representation::digitalSetToImage(squareImage,square);

        Point dimSizes = squareImage.domain().upperBound()
                         - squareImage.domain().lowerBound()
                         + Point(1,1);

        cv::Mat squareOCV = cv::Mat::zeros( dimSizes(1),dimSizes(0),CV_8UC1 );
        DIPaCUS::Representation::imageToCVMat(squareOCV,squareImage);


        DIPaCUS::Properties::boundingBox(bbImage,squareImage);
        DIPaCUS::Properties::boundingBox(bbOCV,squareOCV);

        Point imgBBDimSize = bbImage.ub - bbImage.lb + Point(1,1);
        Point ocvBBDimSize = bbOCV.ub - bbOCV.lb + Point(1,1);

        assert(bbImage.lb!=bbImage.ub);
        assert(imgBBDimSize==ocvBBDimSize);

    }

}}