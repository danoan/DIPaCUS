#include "testCompactSetFromClosedCurve.h"

using namespace DIPaCUS::Test::Derivates;

TestCompactSetFromClosedCurve::TestCompactSetFromClosedCurve()
{
    EuclideanBall2D ecBall(0,0,10);
    DigitalBall gd;
    gd.attach(ecBall);

    Domain domain(ecBall.getLowerBound() + Point(-2,-2),
                  ecBall.getUpperBound() + Point(2,2));

    gd.init(domain.lowerBound(),
            domain.upperBound(),
            1);

    KSpace KImage;
    KImage.init(domain.lowerBound(),
                domain.upperBound(),
                true);

    std::vector<Point> vectorOfPoint;
    SurfelAdjacency SAdj(true);
    SCell bel = Surfaces::findABel(KImage,gd);
    Surfaces::track2DBoundaryPoints(vectorOfPoint,KImage,SAdj,gd,bel);

    Curve c(KImage);
    c.initFromVector(vectorOfPoint);

    DigitalSet ds(domain);
    DIPaCUS::Misc::CompactSetFromClosedCurve<Curve::ConstIterator>(ds,c.begin(),c.end(),false);

    if(visualOutput)
    {
        DGtal::Board2D board;
        board << ds;
        board.saveEPS( std::string(IMAGE_OUTPUT_PATH + "/compactSetFromCurve.eps").c_str() );
    }

}