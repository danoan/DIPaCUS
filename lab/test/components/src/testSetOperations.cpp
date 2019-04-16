#include "testSetOperations.h"

namespace DIPaCUS{ namespace Test{ namespace SetOperations{

    bool testSetDifference(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test setDifference" < Logger::Normal;

        DigitalSet square = DIPaCUS::Shapes::square();
        DigitalSet ball = DIPaCUS::Shapes::ball();

        DigitalSet difference(ball.domain());
        DIPaCUS::SetOperations::setDifference(difference,ball,square);

        logger < Logger::LoggableObject<DigitalSet>(difference,"ball-minus-square.eps");

        bool t1 = difference.size()==92;

        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool testSetIntersection(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test setIntersection" < Logger::Normal;

        DigitalSet square = DIPaCUS::Shapes::square();
        DigitalSet ball = DIPaCUS::Shapes::ball();

        DigitalSet intersection(ball.domain());
        DIPaCUS::SetOperations::setIntersection(intersection,ball,square);

        logger < Logger::LoggableObject<DigitalSet>(intersection,"ball-intersects-ball.eps");

        bool t1 = intersection.size()==225;

        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool runTest(std::ostream& os, const std::string& outputFolder, bool exportObjectsFlag)
    {
        Logger logger(os,outputFolder,exportObjectsFlag);
        logger < Logger::HeaderOne < "Test SetOperations" < Logger::Normal;

        bool flag=true;
        flag = flag && testSetDifference(logger);
        flag = flag && testSetIntersection(logger);

        return flag;
    }

}}}