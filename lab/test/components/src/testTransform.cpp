#include "testTransform.h"

namespace Test{ namespace Transform{

    void testResize()
    {
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

        assert(resizedSquareImgDS.size()==squareDS.size()*4);
    }

    void testInvertColors()
    {
        DigitalSet squareDS = DIPaCUS::Shapes::square();
        Point dimSize = squareDS.domain().upperBound() - squareDS.domain().lowerBound() + Point(1,1);

        Image2D squareImg(squareDS.domain());
        DIPaCUS::Representation::digitalSetToImage(squareImg,squareDS);

        Image2D invertedSquareImg(squareDS.domain());
        DIPaCUS::Transform::invertColors(invertedSquareImg,squareImg);

        DigitalSet invertedSquareDS(squareDS.domain());
        DIPaCUS::Representation::imageAsDigitalSet(invertedSquareDS,invertedSquareImg);

        assert(invertedSquareDS.size()==dimSize(1)*dimSize(0) - squareDS.size());
    }

    void testAddBorder()
    {
        DigitalSet squareDS = DIPaCUS::Shapes::square();

        Image2D squareImg(squareDS.domain());
        DIPaCUS::Representation::digitalSetToImage(squareImg,squareDS);

        Domain extendedDomain(squareImg.domain().lowerBound() - Point(2,2),
                              squareImg.domain().upperBound() + Point(2,2) );
        Image2D resizedSquareImg(extendedDomain);

        Image2D squareImgWithBorder(extendedDomain);
        DIPaCUS::Transform::addBorder(squareImgWithBorder,squareImg,2);

    }

    void testBottomLeftBoundingBoxAtOrigin()
    {
        DigitalSet squareDS = DIPaCUS::Shapes::square();
        Point border(20,20);

        DigitalSet firstQuadrantSquare = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(squareDS,border);

        Point lb,ub;
        firstQuadrantSquare.computeBoundingBox(lb,ub);

        assert(squareDS.size()==firstQuadrantSquare.size());
        assert(lb==border);
        assert(firstQuadrantSquare.domain().lowerBound()==Point(0,0));
    }

    void testExecution()
    {
        testResize();
        testInvertColors();
        testAddBorder();
        testBottomLeftBoundingBoxAtOrigin();
    }

}}