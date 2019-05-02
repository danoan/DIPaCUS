#include "DIPaCUS/components/SetOperations.h"

using namespace DIPaCUS;

void SetOperations::setDifference(DigitalSet &differenceSet,
                                  const DigitalSet &A,
                                  const DigitalSet &B)
{
    assert( differenceSet.domain().isInside( A.domain().lowerBound() ) );
    assert( differenceSet.domain().isInside( A.domain().upperBound() ) );

    differenceSet = A;

    for(auto it=B.begin();it!=B.end();++it)
    {
        differenceSet.erase(*it);
    }
}

void SetOperations::setIntersection(DigitalSet &digitalIntersection,
                                    const DigitalSet &A,
                                    const DigitalSet &B)
{
    for (auto it = A.begin(); it != A.end(); ++it)
    {
        if (B(*it)) digitalIntersection.insert(*it);
    }
}

void SetOperations::setIntersection(DigitalSet &digitalIntersection,
                                    const DigitalSet &A,
                                    const DigitalSet &B,
                                    const Point& translation)
{
    Point tp;
    for (auto it = A.begin(); it != A.end(); ++it)
    {
        tp = *it + translation;
        if (B(tp)) digitalIntersection.insert(tp);
    }
}

