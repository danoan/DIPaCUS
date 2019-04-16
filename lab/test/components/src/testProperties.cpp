#include "testProperties.h"

namespace DIPaCUS{ namespace Test{ namespace Properties{

    bool testCurveBoundingBox(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test curveBoundingBox" < Logger::Normal;

        BoundingBox bbSquare;

        DigitalSet square = DIPaCUS::Shapes::square(1.0,0,0,11);
        BoundingBox groundTruth( BoundingBox::Point(-7,-7), BoundingBox::Point(7,7) );
        Point groundTruthSize = groundTruth.ub - groundTruth.lb + Point(1,1);

        DGtal::Z2i::Curve curve;

        DIPaCUS::Misc::computeBoundaryCurve(curve,square);
        DIPaCUS::Properties::curveBoundingBox(bbSquare,curve.begin(),curve.end());

        Point bbSquareSize = bbSquare.ub - bbSquare.lb + Point(1,1);

        bool t1 = bbSquareSize>=groundTruthSize;

        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool testBoundingBoxOnImage(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test boundingBoxOnImage" < Logger::Normal;
        BoundingBox bbImage;

        DigitalSet square = DIPaCUS::Shapes::square(1.0,0,0,11);
        BoundingBox groundTruth( BoundingBox::Point(-7,-7), BoundingBox::Point(7,7) );

        DIPaCUS::Representation::Image2D squareImage(square.domain());
        DIPaCUS::Representation::digitalSetToImage(squareImage,square);

        Point dimSizes = squareImage.domain().upperBound()
                         - squareImage.domain().lowerBound()
                         + Point(1,1);


        DIPaCUS::Properties::boundingBox(bbImage,squareImage);
        bool t1 = bbImage==groundTruth;

        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool testBoundingBoxOnCVImage(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test boundingBoxOnCVImage" < Logger::Normal;
        BoundingBox bbOCV;

        DigitalSet square = DIPaCUS::Shapes::square(1.0,0,0,11);
        BoundingBox groundTruth( BoundingBox::Point(-7,-7), BoundingBox::Point(7,7) );
        Point groundTruthSize = groundTruth.ub - groundTruth.lb + Point(1,1);

        Point dimSizes = square.domain().upperBound()
                         - square.domain().lowerBound()
                         + Point(1,1);

        cv::Mat squareOCV = cv::Mat::zeros( dimSizes(1),dimSizes(0),CV_8UC1 );
        DIPaCUS::Representation::digitalSetToCVMat(squareOCV,square);

        DIPaCUS::Properties::boundingBox(bbOCV,squareOCV);

        Point ocvBBDimSize = bbOCV.ub - bbOCV.lb + Point(1,1);

        bool t1 = ocvBBDimSize==groundTruthSize;

        logger < "Passed: " < t1 < "\n";

        return t1;

    }

    bool runTest(std::ostream& os, const std::string& outputFolder, bool exportObjectsFlag)
    {
        Logger logger(os,outputFolder,exportObjectsFlag);
        logger < Logger::HeaderOne < "Properties Tests" < Logger::Normal;

        bool flag=true;
        flag = flag && testBoundingBoxOnCVImage(logger);
        flag = flag && testBoundingBoxOnImage(logger);
        flag = flag && testCurveBoundingBox(logger);

        return flag;
    }

}}}