#include "testNeighborhood.h"

namespace Test {namespace Neighborhood{

    void testFourOnBall()
    {
        typedef DIPaCUS::Neighborhood::FourNeighborhoodPredicate FNP;
        DigitalSet boundary = Internal::digitalBoundary<FNP>(DIPaCUS::Shapes::ball());
        assert(boundary.size()==76);
    }

    void testEightOnBall()
    {
        typedef DIPaCUS::Neighborhood::EightNeighborhoodPredicate ENP;
        DigitalSet boundary = Internal::digitalBoundary<ENP>(DIPaCUS::Shapes::ball());
        assert(boundary.size()==56);
    }

    void testComplementEquivalence()
    {
        typedef DIPaCUS::Neighborhood::FourNeighborhoodPredicate FNP;
        typedef DIPaCUS::Neighborhood::EightNeighborhoodPredicate ENP;

        DigitalSet ball = DIPaCUS::Shapes::ball();
        DigitalSet fourBoundaryBall = Internal::digitalBoundary<FNP>(ball);


        DigitalSet ballComplement = Internal::digitalComplement(ball);
        DigitalSet eightBoundaryBallComplement = Internal::digitalBoundary<ENP>(ballComplement);

        for(auto it=ballComplement.domain().begin();it!=ballComplement.domain().end();++it)
        {
            DGtal::Z2i::Point p = *it;
            if(p(0)==ballComplement.domain().lowerBound()(0) ||
               p(1)==ballComplement.domain().lowerBound()(1) ) eightBoundaryBallComplement.erase(*it);

            if(p(0)==ballComplement.domain().upperBound()(0) ||
               p(1)==ballComplement.domain().upperBound()(1) ) eightBoundaryBallComplement.erase(*it);
        }


        //Incident pixels to curve linels must be exactly the pixels on fourBoundaryBall and
        //eightBoundarBallComplement sets
        DGtal::Z2i::KSpace KSpace;
        DGtal::Z2i::Curve curve;

        KSpace.init(ball.domain().lowerBound(),ball.domain().upperBound(),true);
        Utils::computeBoundaryCurve(ball,curve);
        for(auto it=curve.begin();it!=curve.end();++it)
        {
            DGtal::Z2i::SCells pixels = KSpace.sUpperIncident(*it);
            assert( pixels.size()==2 );
            for(auto itp=pixels.begin();itp!=pixels.end();++itp)
            {

                assert(fourBoundaryBall(KSpace.sCoords(*itp)) ||
                       eightBoundaryBallComplement(KSpace.sCoords(*itp)) );
            }
        }


    }
}}

namespace Test {namespace Neighborhood { namespace Internal{

    DigitalSet digitalComplement(const DigitalSet& ds)
    {
        typedef DIPaCUS::Neighborhood::EightNeighborhoodPredicate ENP;

        DGtal::Z2i::Point border(2,2);
        DGtal::Z2i::Domain extendedDomain(ds.domain().lowerBound() - border,
                                          ds.domain().upperBound() + border);

        DigitalSet dsComplement(extendedDomain);
        dsComplement.assignFromComplement(dsComplement);
        DigitalSet extendedDomainBoundary = Internal::digitalBoundary<ENP>(dsComplement);
        for(auto it=ds.begin();it!=ds.end();++it)
        {
            if(dsComplement.erase(*it));
        }

        return dsComplement;
    }

}}}