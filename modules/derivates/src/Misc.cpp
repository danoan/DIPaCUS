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
                                                                                        _ds(extendDS(intersectWith,_r)),
                                                                                        _ball(DIPaCUS::Shapes::ball(1.0,0,0,r))
    {}
        
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

    void getConnectedComponents( std::vector<ConnectedComponent>& vcc, const DigitalSet& ds)
    {
        PointMarker markers;
        for(auto it=ds.begin();it!=ds.end();++it)
        {
            Point p = *it;
            if(markers.find(p)!=markers.end()) continue;

            vcc.push_back(std::set<Point>());
            exploreComponent(vcc[vcc.size()-1],p, markers,ds);
        }
    }

    void exploreComponent(ConnectedComponent& cc,Point& p, PointMarker& markers, const DigitalSet& ds)
    {
        Point neigh[4]={Point(0,1),Point(1,0),Point(-1,0),Point(0,-1)};
        std::stack<Point> s;
        s.push(p);
        while(!s.empty())
        {
            Point p = s.top(); s.pop();
            if(markers.find(p)!=markers.end()) continue;
            markers.insert(p);
            cc.insert(p);

            for(int i=0;i<4;++i)
            {
                Point np = p+neigh[i];
                if(!ds(np)) continue;
                if(markers.find(np)!=markers.end()) continue;
                s.push(np);
            }
        }
    }

    DigitalSet cleanSet(const DigitalSet& ds)
    {
        std::vector<ConnectedComponent> cc;
        DIPaCUS::Misc::getConnectedComponents(cc,ds);
        std::sort(cc.begin(),cc.end(),[](const ConnectedComponent& s1, const ConnectedComponent& s2){ return s1.size() > s2.size(); });

        DigitalSet dsOut(ds.domain());
        dsOut.insert(cc[0].begin(),cc[0].end());

        Point lb,ub;
        dsOut.computeBoundingBox(lb,ub);
        Domain domain(lb,ub);

        DigitalSet dsInversion(domain);
        dsInversion.clear();
        dsInversion.assignFromComplement(dsOut);

        DGtal::Z2i::Point np4[4]={Point(0,1),Point(1,0),Point(-1,0),Point(0,-1)};
        for(auto p:dsInversion)
        {
            bool fill=true;
            for(auto n:np4)
            {
                if(dsInversion(p+n))
                {
                    fill=false;
                    break;
                }
            }
            if(fill) dsOut.insert(p);
        }

        return dsOut;
    }

}}