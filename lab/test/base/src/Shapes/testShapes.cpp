#include "Shapes/testShapes.h"

void Test::Shapes::testExecution()
{
    typedef DIPaCUS::Shapes::DigitalSet DigitalSet;

    DigitalSet triangle = DIPaCUS::Shapes::triangle();
    DigitalSet square = DIPaCUS::Shapes::square();
    DigitalSet ball = DIPaCUS::Shapes::ball();
    DigitalSet flower = DIPaCUS::Shapes::flower();

    DGtal::Z2i::Point border(10,10);

    DGtal::Z2i::Domain domain(flower.domain().lowerBound()-border,
                              flower.domain().upperBound()+border);

    assert(triangle.size()==131);
    assert(square.size()==225);
    assert(ball.size()==317);
    assert(flower.size()==441);
}