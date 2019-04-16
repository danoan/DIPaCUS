#include "Shapes/testShapes.h"

namespace DIPaCUS
{
    bool Test::Shapes::testTriangle(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test Triangle" < Logger::Normal;

        DigitalSet triangle = DIPaCUS::Shapes::triangle();
        logger < Logger::LoggableObject<DigitalSet>(triangle,"triangle.eps");

        bool t1 = triangle.size()==131;
        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool Test::Shapes::testSquare(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test Square" < Logger::Normal;

        DigitalSet square = DIPaCUS::Shapes::square();
        logger < Logger::LoggableObject<DigitalSet>(square,"square.eps");

        bool t1 = square.size()==225;
        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool Test::Shapes::testFlower(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test Flower" < Logger::Normal;

        DigitalSet flower = DIPaCUS::Shapes::flower();
        logger < Logger::LoggableObject<DigitalSet>(flower,"flower.eps");

        bool t1 = flower.size()==441;
        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool Test::Shapes::testBall(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test Ball" < Logger::Normal;

        DigitalSet ball = DIPaCUS::Shapes::ball();
        logger < Logger::LoggableObject<DigitalSet>(ball,"ball.eps");

        bool t1 = ball.size()==317;
        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool Test::Shapes::testNGon(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test NGon" < Logger::Normal;

        DigitalSet pentagon = DIPaCUS::Shapes::NGon(1.0,0,0,20,5,0);
        logger < Logger::LoggableObject<DigitalSet>(pentagon,"ngon.eps");

        bool t1 = pentagon.size()==960;
        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool Test::Shapes::runTest(std::ostream& os, const std::string& outputFolder, bool exportObjectsFlag)
    {
        Logger logger(os,outputFolder,exportObjectsFlag);
        logger < Logger::HeaderOne < "Test Shapes" < Logger::Normal;

        bool flag=true;

        flag = flag && testTriangle(logger);
        flag = flag && testSquare(logger);
        flag = flag && testBall(logger);
        flag = flag && testFlower(logger);
        flag = flag && testNGon(logger);

        return flag;
    }
}