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
