#include "DIPaCUS/components/SetOperations.h"

using namespace DIPaCUS;

void SetOperations::setDifference(DigitalSet &differenceSet,
                                  const DigitalSet &A,
                                  const DigitalSet &B)
{
    Point lbIn = A.domain().lowerBound();
    Point ubIn = A.domain().upperBound();
    Point lbOut = differenceSet.domain().lowerBound();
    Point ubOut = differenceSet.domain().upperBound();

    assert(lbOut(0) <= lbIn(0));
    assert(lbOut(1) <= lbIn(1));

    assert(ubOut(0)>=ubIn(0));
    assert(ubOut(1)>=ubIn(1));

    Domain domain = A.domain();

    DigitalSet temp(domain);
    DigitalSetInserter diTemp(temp);
    A.computeComplement(diTemp);
    temp += B;

    DigitalSetInserter diDiff(differenceSet);
    temp.computeComplement(diDiff);
}

void SetOperations::setIntersection(DigitalSet &digitalIntersection,
                                    const DigitalSet &A,
                                    const DigitalSet &B)
{
    Point lbIn = A.domain().lowerBound();
    Point ubIn = A.domain().upperBound();
    Point lbOut = digitalIntersection.domain().lowerBound();
    Point ubOut = digitalIntersection.domain().upperBound();

    assert(lbOut(0) <= lbIn(0));
    assert(lbOut(1) <= lbIn(1));

    assert(ubOut(0)>=ubIn(0));
    assert(ubOut(1)>=ubIn(1));

    Domain domain = A.domain();

    for (auto it = A.begin(); it != A.end(); ++it)
    {
        if (B(*it)) digitalIntersection.insert(*it);
    }
}

