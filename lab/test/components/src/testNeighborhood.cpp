#include "testNeighborhood.h"

namespace DIPaCUS{ namespace Test {namespace Neighborhood{

    bool testFourOnBall(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test FourNeighborhood on a Ball" < Logger::Normal;

        typedef DIPaCUS::Neighborhood::FourNeighborhoodPredicate FNP;
        DigitalSet boundary = Internal::digitalBoundary<FNP>(DIPaCUS::Shapes::ball());

        logger < Logger::LoggableObject<DigitalSet>(boundary,"fourN-ball.eps");

        bool t1 = boundary.size()==76;
        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool testEightOnBall(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test EightNeighborhood on a Ball" < Logger::Normal;

        typedef DIPaCUS::Neighborhood::EightNeighborhoodPredicate ENP;
        DigitalSet boundary = Internal::digitalBoundary<ENP>(DIPaCUS::Shapes::ball());

        logger < Logger::LoggableObject<DigitalSet>(boundary,"eigthN-ball.eps");

        bool t1 = boundary.size()==56;
        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool testComplementEquivalence(Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test ComplementEquivalence on a Ball" < Logger::Normal;

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

        bool t1=true;
        KSpace.init(ball.domain().lowerBound(),ball.domain().upperBound(),true);
        DIPaCUS::Misc::computeBoundaryCurve(curve,ball);
        for(auto it=curve.begin();it!=curve.end();++it)
        {
            DGtal::Z2i::SCells pixels = KSpace.sUpperIncident(*it);
            assert( pixels.size()==2 );
            for(auto itp=pixels.begin();itp!=pixels.end();++itp)
            {

                t1 = t1 && (fourBoundaryBall(KSpace.sCoords(*itp)) ||
                        eightBoundaryBallComplement(KSpace.sCoords(*itp)) );
            }
        }

        logger < "Passed: " < t1 < "\n";

        return t1;
    }

    bool runTest(std::ostream& os, const std::string& outputFolder, bool exportObjectsFlag)
    {
        Logger logger(os,outputFolder,exportObjectsFlag);
        logger < Logger::HeaderOne < "Neighborhood Tests" < Logger::Normal;

        bool flag = true;
        flag = flag && testFourOnBall(logger);
        flag = flag && testEightOnBall(logger);
        flag = flag && testComplementEquivalence(logger);

        return flag;
    }
}}}

namespace DIPaCUS{ namespace Test {namespace Neighborhood { namespace Internal{

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

}}}}