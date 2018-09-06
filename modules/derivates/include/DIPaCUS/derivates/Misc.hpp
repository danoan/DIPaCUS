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

template<typename TIterator>
InvertCurve<TIterator>::InvertCurve(const KSpace& KImage,
                                    TIterator begin,
                                    TIterator end,
                                    Curve& c2)
{
    std::vector<SCell> SCells;
    auto it=begin;
    do{
        SCells.push_back(*it);
        ++it;
    }while(it!=end);

    std::vector<SCell> newSCells;
    {
        auto it = SCells.rbegin();
        do{
            SCell newLinel = KImage.sCell( *it);
            KImage.sSetSign(newLinel,!KImage.sSign(*it));

            newSCells.push_back(newLinel);
            ++it;
        }while(it!=SCells.rend());
    }

    c2.initFromSCellsVector(newSCells);
}