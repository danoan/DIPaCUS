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

template<class TSCellIterator>
CompactSetFromClosedCurve<TSCellIterator>::CompactSetFromClosedCurve(DigitalSet& ds,
                                                                     TSCellIterator itb,
                                                                     TSCellIterator ite,
                                                                     bool ccw)
{
    KSpace KImage;
    KImage.init(ds.domain().lowerBound(),ds.domain().upperBound(),true);
    const Domain& domain = ds.domain();

    KSpace::SCell boundaryPixel;
    if(ccw)
        boundaryPixel = KImage.sDirectIncident(*itb, KImage.sOrthDir(*itb));
    else
        boundaryPixel = KImage.sIndirectIncident(*itb, KImage.sOrthDir(*itb));

    DigitalSet fakeBoundary(domain);
    TSCellIterator it = itb;
    do{
        if(ccw)
            fakeBoundary.insert( KImage.sCoords( KImage.sIndirectIncident(*it,KImage.sOrthDir(*it)) ) );
        else
            fakeBoundary.insert( KImage.sCoords( KImage.sDirectIncident(*it,KImage.sOrthDir(*it)) ) );
        ++it;
    }while(it!=ite);

    DIPaCUS::Misc::FillInterior(ds,KImage.sCoords(boundaryPixel),fakeBoundary);
    for(auto it=fakeBoundary.begin();it!=fakeBoundary.end();++it)
        ds.erase(*it);
}