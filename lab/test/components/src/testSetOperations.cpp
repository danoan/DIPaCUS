#include "testSetOperations.h"

namespace Test{ namespace SetOperations{

    void testExecution()
    {
        DigitalSet square = DIPaCUS::Shapes::square();
        DigitalSet ball = DIPaCUS::Shapes::ball();

        DigitalSet difference(ball.domain());
        DIPaCUS::SetOperations::setDifference(difference,ball,square);

        assert(difference.size()==92);

        DigitalSet intersection(ball.domain());
        DIPaCUS::SetOperations::setIntersection(intersection,ball,square);

        assert(intersection.size()==225);

    }

}}