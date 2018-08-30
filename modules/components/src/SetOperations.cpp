#include "DIPaCUS/components/SetOperations.h"

using namespace DIPaCUS::SetOperations;

SetDifference::SetDifference(DigitalSet &differenceSet,
                             const DigitalSet &A,
                             const DigitalSet &B)
{
    Domain domain = A.domain();

    DigitalSet temp(domain);
    DigitalSetInserter diTemp(temp);
    A.computeComplement(diTemp);
    temp += B;

    DigitalSetInserter diDiff(differenceSet);
    temp.computeComplement(diDiff);
}

SetIntersection::SetIntersection(DigitalSet &digitalIntersection,
                                 const DigitalSet &A,
                                 const DigitalSet &B)
{
    Domain domain = A.domain();

    for (auto it = A.begin(); it != A.end(); ++it)
    {
        if (B(*it)) digitalIntersection.insert(*it);
    }
}

