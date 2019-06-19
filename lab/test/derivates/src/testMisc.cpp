#include "testMisc.h"

namespace DIPaCUS{ namespace Test{ namespace Misc{

    bool testDigitalBallIntersection(Logger& logger)
    {
        typedef DGtal::Z2i::Point Point;

        logger < Logger::HeaderTwo < "Test digitalBallIntersection" < Logger::Normal;

        DigitalSet square = DIPaCUS::Shapes::square(1.0,0,0,10);
        DIPaCUS::Misc::DigitalBallIntersection DBI(5,square);

        DigitalSet intersection(square.domain());
        DBI(intersection, Point(-7,7));

        logger < Logger::LoggableObject<DigitalSet>(intersection,"square-ball-intersection.eps");

        bool t1 = intersection.size()==26;
        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool testDigitalBoundaryAndFillInterior(Logger& logger)
    {
        typedef DGtal::Z2i::Point Point;

        logger < Logger::HeaderTwo < "Test digitalBoundary and fillInterior" < Logger::Normal;

        DigitalSet flower = DIPaCUS::Shapes::flower(1.0,0,0,30,10,3);

        DigitalSet boundary(flower.domain());
        DIPaCUS::Misc::digitalBoundary<DIPaCUS::Neighborhood::FourNeighborhoodPredicate>(boundary,flower);

        DigitalSet interior(flower.domain());
        DIPaCUS::SetOperations::setDifference(interior,flower,boundary);
        Point interiorPoint = *interior.begin();

        DigitalSet reconstructed(flower.domain());
        DIPaCUS::Misc::fillInterior(reconstructed,interiorPoint,boundary);

        logger < Logger::LoggableObject<DigitalSet>(boundary,"flower-four-boundary.eps");

        bool t1 = reconstructed.size()==flower.size();
        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool testGetBorder(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test getBorder" < Logger::Normal;

        DigitalSet square = DIPaCUS::Shapes::square(1.0,0,0,10);
        DigitalSet border(square.domain());

        DigitalSet bound1(square.domain());
        DIPaCUS::Misc::digitalBoundary<DIPaCUS::Neighborhood::FourNeighborhoodPredicate>(bound1,square);

        DigitalSet partialSquare(square.domain());
        DIPaCUS::SetOperations::setDifference(partialSquare,square,bound1);

        DigitalSet bound2(square.domain());
        DIPaCUS::Misc::digitalBoundary<DIPaCUS::Neighborhood::FourNeighborhoodPredicate>(bound2,partialSquare);

        DigitalSet compare(square.domain());
        compare.insert(bound1.begin(),bound1.end());
        compare.insert(bound2.begin(),bound2.end());

        DIPaCUS::Misc::getBorder(border,square,2);

        logger < Logger::LoggableObject<DigitalSet>(border,"square-border-tick2.eps");

        bool t1 = compare.size()==border.size();
        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool testInvertCurve(Logger& logger)
    {
        typedef DGtal::Z2i::Curve Curve;
        typedef DGtal::Z2i::KSpace KSpace;
        typedef DGtal::Z2i::Domain Domain;

        logger < Logger::HeaderTwo < "Test invertCurve" < Logger::Normal;

        DigitalSet ball = DIPaCUS::Shapes::ball();
        const Domain& domain = ball.domain();

        Curve curve;
        DIPaCUS::Misc::computeBoundaryCurve(curve,ball);

        KSpace KImage;
        KImage.init(domain.lowerBound(),domain.upperBound(),true);

        Curve invertedCurve;
        DIPaCUS::Misc::invertCurve(invertedCurve,KImage,curve.begin(),curve.end());

        DigitalSet compactSet(domain);
        DIPaCUS::Misc::compactSetFromClosedCurve(compactSet,invertedCurve.begin(),invertedCurve.end(),false);

        logger < Logger::LoggableObject<DigitalSet>(compactSet,"invertCurve-compact-set.eps");

        bool t1 = compactSet.size() == ball.size();
        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool testComputeBoundaryCurve(const Image2D& imgIn, const std::string& name, Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test computeBoundaryCurve for " + name < Logger::Normal;

        Curve curve;
        DIPaCUS::Misc::computeBoundaryCurve(curve,imgIn,1);

        logger < Logger::LoggableObject<Curve>(curve,"boundary-curve-"+name+".eps");

        bool t1 = curve.isValid();
        bool t2 = curve.isClosed();

        logger < "Passed (connected): " < t1 < "\n";
        logger < "Passed (closed): " < t2 < "\n";

        return t1 && t2;

    }

    bool testComputeBoundaryCurve(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test computeBoundaryCurve for ball" < Logger::Normal;

        Curve curve;
        DigitalSet ball = DIPaCUS::Shapes::ball();
        DIPaCUS::Misc::computeBoundaryCurve(curve,ball);

        logger < Logger::LoggableObject<Curve>(curve,"boundary-curve-ball.eps");

        bool t1 = curve.isValid();
        bool t2 = curve.isClosed();

        logger < "Passed (connected): " < t1 < "\n";
        logger < "Passed (closed): " < t2 < "\n";

        return t1 && t2;

    }

    bool testCompactSetFromClosedCurve(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test compactSetFromClosedCurve" < Logger::Normal;

        DigitalSet dsIn = DIPaCUS::Shapes::ball(1.0,0,0,10);
        Curve curve;
        DIPaCUS::Misc::computeBoundaryCurve(curve,dsIn);

        logger < Logger::LoggableObject<Curve>(curve,"closed-curve.eps");

        DigitalSet dsOut(dsIn.domain());
        DIPaCUS::Misc::compactSetFromClosedCurve(dsOut,curve.begin(),curve.end(),true);

        logger < Logger::LoggableObject<DigitalSet>(dsOut,"compact-set-from-ball-bound.eps");

        bool t1 = dsOut.size()==dsIn.size();
        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool testConnectedComponents(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test getConnectedComponents" < Logger::Normal;

        DigitalSet square1 = DIPaCUS::Shapes::square(1.0,0,0,20,0);
        DigitalSet square2 = DIPaCUS::Shapes::square(1.0,0,0,15,0);
        DigitalSet square3 = DIPaCUS::Shapes::square(1.0,0,0,10,0);

        DigitalSet diff(square1.domain());
        DIPaCUS::SetOperations::setDifference(diff,square1,square2);
        square3.insert(diff.begin(),diff.end());

        std::vector< DIPaCUS::Misc::ConnectedComponent > vcc1;
        DIPaCUS::Misc::getConnectedComponents(vcc1,square1);

        std::vector< DIPaCUS::Misc::ConnectedComponent > vcc3;
        DIPaCUS::Misc::getConnectedComponents(vcc3,square3);

        bool t1 = vcc1.size()==1 && vcc3.size()==2;
        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool runTest(std::ostream& os,
                 const std::string& outputFolder,
                 bool exportObjectsFlag)
    {
        Logger logger(os,outputFolder,exportObjectsFlag);
        logger < Logger::HeaderOne < "Test Misc" < Logger::Normal;

        bool flag = testDigitalBallIntersection(logger);
        flag = flag && testDigitalBoundaryAndFillInterior(logger);
        flag = flag && testGetBorder(logger);
        flag = flag && testInvertCurve(logger);

        flag = flag && testComputeBoundaryCurve(Data::square,"square",logger);
        flag = flag && testComputeBoundaryCurve(Data::squareConcavity,"square-concavity",logger);
        flag = flag && testComputeBoundaryCurve(Data::squareHole,"square-hole",logger);
        flag = flag && testComputeBoundaryCurve(Data::squareShorts,"square-shorts",logger);

        flag = flag && testComputeBoundaryCurve(logger);

        flag = flag && testCompactSetFromClosedCurve(logger);
        flag = flag && testConnectedComponents(logger);


        return flag;
    }

}}}