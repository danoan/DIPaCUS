#include "Misc.h"

using namespace DIPaCUS::Misc;

template<typename TNeighborhood>
DigitalBoundary<TNeighborhood>::DigitalBoundary(DigitalSet &boundaryDS,
                                                const DigitalSet &originalDS)
{
    NeighborhoodPredicate NP(originalDS);
    DigitalSetInserter inserter(boundaryDS);

    std::remove_copy_if(originalDS.begin(), originalDS.end(), inserter, NP);
}