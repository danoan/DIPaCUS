#include "testTransform.h"

namespace DIPaCUS{ namespace Test{ namespace Transform{

    bool testResize(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test resize" < Logger::Normal;

        DigitalSet squareDS = DIPaCUS::Shapes::square();

        Image2D squareImg(squareDS.domain());
        DIPaCUS::Representation::digitalSetToImage(squareImg,squareDS);

        Point dimSize = squareImg.domain().upperBound() - squareImg.domain().lowerBound() + Point(1,1);

        Domain extendedDomain(squareImg.domain().lowerBound() - dimSize/2 - Point(1,1),
                              squareImg.domain().upperBound() + dimSize/2 + Point(1,1));
        Image2D resizedSquareImg(extendedDomain);
        DIPaCUS::Transform::resize(resizedSquareImg,squareImg,2.0);

        DigitalSet resizedSquareImgDS(extendedDomain);
        DIPaCUS::Representation::imageAsDigitalSet(resizedSquareImgDS,resizedSquareImg);

        logger < Logger::LoggableObject<DigitalSet>(resizedSquareImgDS,"resized-square.eps");

        bool t1 = resizedSquareImgDS.size()==squareDS.size()*4;
        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool testInvertColors(Logger& logger)
    {
        DigitalSet squareDS = DIPaCUS::Shapes::square();
        Point dimSize = squareDS.domain().upperBound() - squareDS.domain().lowerBound() + Point(1,1);

        Image2D squareImg(squareDS.domain());
        DIPaCUS::Representation::digitalSetToImage(squareImg,squareDS);

        Image2D invertedSquareImg(squareDS.domain());
        DIPaCUS::Transform::invertColors(invertedSquareImg,squareImg);

        DigitalSet invertedSquareDS(squareDS.domain());
        DIPaCUS::Representation::imageAsDigitalSet(invertedSquareDS,invertedSquareImg);

        bool t1 = invertedSquareDS.size()==dimSize(1)*dimSize(0) - squareDS.size();
        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool testAddBorder(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test addBorder" < Logger::Normal;

        DigitalSet squareDS = DIPaCUS::Shapes::square();

        Image2D squareImg(squareDS.domain());
        DIPaCUS::Representation::digitalSetToImage(squareImg,squareDS);

        Domain extendedDomain(squareImg.domain().lowerBound() - Point(2,2),
                              squareImg.domain().upperBound() + Point(2,2) );
        Image2D resizedSquareImg(extendedDomain);

        Image2D squareImgWithBorder(extendedDomain);
        DIPaCUS::Transform::addBorder(squareImgWithBorder,squareImg,2);

        logger < Logger::LoggableObject<Image2D>(squareImgWithBorder,"square-with-border.pgm");

        return true;

    }

    bool testBottomLeftBoundingBoxAtOrigin(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test bottomLeftBoundingAtOrigin" < Logger::Normal;

        DigitalSet squareDS = DIPaCUS::Shapes::square();
        Point padding(20,20);

        DigitalSet firstQuadrantSquare = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(squareDS,padding);

        Point lb,ub;
        firstQuadrantSquare.computeBoundingBox(lb,ub);

        bool t1 = squareDS.size()==firstQuadrantSquare.size();
        bool t2 = lb==padding;
        bool t3 = firstQuadrantSquare.domain().lowerBound()==Point(0,0);

        logger < "Passed(size): " < t1 < "\n";
        logger < "Passed(padding-creation): " < t2 < "\n";
        logger < "Passed(lb-at-origin): " < t3 < "\n";


        return t1 && t2 && t3;
    }

    bool runTest(std::ostream& os, const std::string& outputFolder, bool exportObjectsFlag)
    {
        Logger logger(os,outputFolder,exportObjectsFlag);

        logger < Logger::HeaderOne < "Test Transform" < Logger::Normal;

        bool flag=true;
        flag = flag && testResize(logger);
        flag = flag && testInvertColors(logger);
        flag = flag && testAddBorder(logger);
        flag = flag && testBottomLeftBoundingBoxAtOrigin(logger);

        return flag;
    }

}}}