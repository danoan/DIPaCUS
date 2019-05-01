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

    template<typename TSCellIterator>
    void invertCurve(Curve& cOut,
                     const KSpace& KImage,
                     TSCellIterator begin,
                     TSCellIterator end)
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

        cOut.initFromSCellsVector(newSCells);
    }

    template<class TSCellIterator>
    void compactSetFromClosedCurve(DigitalSet& dsOut,
                                   TSCellIterator itb,
                                   TSCellIterator ite,
                                   bool ccw)
    {
        KSpace KImage;

        //Using extended domain because IndirectIncident may access
        //an invalid scell in a tight domain.
        Domain extDomain( dsOut.domain().lowerBound() - Point(1,1), dsOut.domain().upperBound() + Point(1,1) );

        KImage.init(extDomain.lowerBound(),extDomain.upperBound(),true);



        KSpace::SCell boundaryPixel;
        if(ccw)
            boundaryPixel = KImage.sDirectIncident(*itb, KImage.sOrthDir(*itb));
        else
            boundaryPixel = KImage.sIndirectIncident(*itb, KImage.sOrthDir(*itb));

        DigitalSet fakeBoundary(extDomain);
        TSCellIterator it = itb;
        do
        {
            if(ccw)
                fakeBoundary.insert( KImage.sCoords( KImage.sIndirectIncident(*it,KImage.sOrthDir(*it)) ) );
            else
                fakeBoundary.insert( KImage.sCoords( KImage.sDirectIncident(*it,KImage.sOrthDir(*it)) ) );
            ++it;
        }while(it!=ite);

        fillInterior(dsOut,KImage.sCoords(boundaryPixel),fakeBoundary);
        for(auto it=fakeBoundary.begin();it!=fakeBoundary.end();++it)
            dsOut.erase(*it);
    }


}}

