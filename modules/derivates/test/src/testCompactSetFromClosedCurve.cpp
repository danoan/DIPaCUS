#include "testCompactSetFromClosedCurve.h"

using namespace DIPaCUS::Test::Derivates;

TestCompactSetFromClosedCurve::DigitalSet TestCompactSetFromClosedCurve::digitalSetFromDigitizer(const DigitalBall& db)
{
    const Domain& domain = db.getDomain();
    DigitalSet ds(domain);
    for(auto it=domain.begin();it!=domain.end();++it)
    {
        if( db(*it) ) ds.insert(*it);
    }

    return ds;
}

TestCompactSetFromClosedCurve::CurveAndDS TestCompactSetFromClosedCurve::ball(double radius)
{
    EuclideanBall2D ecBall(0,0,radius);
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

    return CurveAndDS(c,digitalSetFromDigitizer(gd));
}

void TestCompactSetFromClosedCurve::creationTest()
{
    CurveAndDS cd = ball(10);

    Curve& c = cd.curve;
    DigitalSet& dsDig = cd.digitalSet;
    const Domain& domain = dsDig.domain();

    DigitalSet ds(domain);
    DIPaCUS::Misc::CompactSetFromClosedCurve<Curve::ConstIterator>(ds,c.begin(),c.end(),true);

    //Correctness Test
    assert(ds.size()==dsDig.size());

    if(visualOutput)
    {
        DGtal::Board2D board;
        board << ds;
        board.saveEPS( std::string(IMAGE_OUTPUT_PATH + "/compactSetFromCurve.eps").c_str() );
    }

}


TestCompactSetFromClosedCurve::TestCompactSetFromClosedCurve()
{
    creationTest();
}