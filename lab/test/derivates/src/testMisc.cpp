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

    bool runTest(std::ostream& os,
                 const std::string& outputFolder,
                 bool exportObjectsFlag)
    {
        Logger logger(os,outputFolder,exportObjectsFlag);
        logger < Logger::HeaderOne < "Test Misc" < Logger::Normal;

        bool flag = testDigitalBallIntersection(logger);
        flag = flag && testComputeBoundaryCurve(Data::square,"square",logger);
        flag = flag && testComputeBoundaryCurve(Data::squareConcavity,"square-concavity",logger);
        flag = flag && testComputeBoundaryCurve(Data::squareHole,"square-hole",logger);
        flag = flag && testComputeBoundaryCurve(Data::squareShorts,"square-shorts",logger);

        flag = flag && testComputeBoundaryCurve(logger);

        flag = testCompactSetFromClosedCurve(logger);


        return flag;
    }

}}}