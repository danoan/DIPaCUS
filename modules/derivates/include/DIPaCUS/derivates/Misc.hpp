#include "Misc.h"

namespace DIPaCUS{ namespace Misc{
    template<typename TNeighborhood>
    void digitalBoundary(DigitalSet &boundaryDS,
                         const DigitalSet &originalDS)
    {
        typedef TNeighborhood NeighborhoodPredicate;
        typedef DGtal::DigitalSetInserter<DigitalSet> DigitalSetInserter;

        NeighborhoodPredicate NP(originalDS);
        DigitalSetInserter inserter(boundaryDS);

        std::remove_copy_if(originalDS.begin(), originalDS.end(), inserter, NP);
    }


}}