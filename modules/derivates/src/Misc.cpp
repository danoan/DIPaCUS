#include <DIPaCUS/components/Properties.h>
#include "DIPaCUS/derivates/Misc.h"

namespace DIPaCUS{ namespace Misc{

    Domain DigitalBallIntersection::extendDomain(const DigitalSet& ds,Radius r)
    {
        return Domain( ds.domain().lowerBound() - Point(r,r), ds.domain().upperBound() + Point(r,r) );
    }

    DigitalSet DigitalBallIntersection::extendDS(const DigitalSet& ds,Radius r)
    {
        Domain extDomain = extendDomain(ds,r);
        DigitalSet temp(extDomain);
        temp = ds;

        return temp;
    }

    DigitalBallIntersection::DigitalBallIntersection(Radius r,
                                                     const DigitalSet &intersectWith) : _r(r),
                                                                                        _extDomain(extendDomain(intersectWith,_r)),
                                                                                        _ds(extendDS(intersectWith,_r))
    {}

    void DigitalBallIntersection::operator()(DigitalSet &intersectionSet,
                                             Point center)
    {
        DigitalSet db(_extDomain);
        db = DIPaCUS::Shapes::ball(1.0,center[0],center[1],_r);

        DIPaCUS::SetOperations::setIntersection(intersectionSet, db, _ds);
    }


    void fillInterior(DigitalSet &dsOut,
                      const Point &pt,
                      const DigitalSet &boundIn)
    {
        dsOut.insert(boundIn.begin(), boundIn.end());

        Point currentPoint, candidatePoint;
        Point neighborFilter[4] = {Point(1, 0), Point(-1, 0), Point(0, 1), Point(0, -1)};

        std::stack<Point> toVisit;

        toVisit.push(pt);
        while (!toVisit.empty()) {
            currentPoint = toVisit.top();
            dsOut.insert(currentPoint);
            toVisit.pop();

            for (int i = 0; i < 4; ++i) {
                candidatePoint = currentPoint + neighborFilter[i];
                if (dsOut.find(candidatePoint) != dsOut.end()) continue;
                toVisit.push(candidatePoint);
            }
        }
    }


    void getBorder(DigitalSet &dsOut,
                   const DigitalSet &dsIn,
                   Thickness t)
    {
        Domain domain = dsIn.domain();

        DigitalSet eroded(domain);
        Morphology::erode(eroded,
                          dsIn,
                          Morphology::StructuringElement(Morphology::StructuringElement::RECT,
                                                         t) );

        DIPaCUS::SetOperations::setDifference(dsOut, dsIn, eroded);
    }

    void computeBoundaryCurve(Curve &boundOut,
                              const Image2D &imgIn,
                              ThresholdValue tv)
    {
        DigitalSet dsOut(imgIn.domain());
        DIPaCUS::Representation::imageAsDigitalSet(dsOut,imgIn);

        computeBoundaryCurve(boundOut,dsOut);
    }


    void computeBoundaryCurve(Curve& boundOut,
                              const DigitalSet& dsIn)
    {
        typedef DGtal::Z2i::KSpace KSpace;
        typedef DGtal::Z2i::Domain Domain;

        typedef DGtal::SurfelAdjacency<KSpace::dimension> SurfelAdjacency;
        typedef DGtal::Surfaces<KSpace> Surfaces;

        typedef DGtal::functors::SimpleThresholdForegroundPredicate<Image2D> ThreshPredicate;

        //Using extended domain because tracker has difficult to continue
        //when using a tight domain.
        Domain extDomain( dsIn.domain().lowerBound() - Point(1,1), dsIn.domain().upperBound() + Point(1,1) );
        KSpace KImage;

        KImage.init(extDomain.lowerBound(),extDomain.upperBound(),true);

        DGtal::Z2i::SCell imageBel = Surfaces::findABel(KImage, dsIn, 10000);

        SurfelAdjacency SAdj(true);

        std::vector<DGtal::Z2i::SCell> boundarySCells;
        Surfaces::track2DBoundary(boundarySCells,
                                  KImage,
                                  SAdj,
                                  dsIn,
                                  imageBel);

        boundOut.initFromSCellsVector(boundarySCells);

        DIPaCUS::Transform::eliminateLoops(boundOut,KImage,boundOut);
    }

    void invertCurve(Curve& cOut,
                     const KSpace& KImage,
                     SCellIterator begin,
                     SCellIterator end)
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

    void compactSetFromClosedCurve(DigitalSet& dsOut,
                                   SCellIterator itb,
                                   SCellIterator ite,
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
        SCellIterator it = itb;
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