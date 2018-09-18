#ifndef TEST_DIPACUS_DERIVATES_MISC_H
#define TEST_DIPACUS_DERIVATES_MISC_H

#include "DGtal/helpers/StdDefs.h"

#include "DGtal/geometry/curves/StabbingCircleComputer.h"
#include "DGtal/geometry/curves/estimation/MostCenteredMaximalSegmentEstimator.h"

#include "DGtal/io/boards/Board2D.h"

#include "DIPaCUS/derivates/Misc.h"

namespace DIPaCUS
{
    namespace Test 
    {
        extern std::string IMAGE_INPUT_PATH;
        extern std::string IMAGE_OUTPUT_PATH;

        extern bool verbose;
        extern bool visualOutput;
        
        namespace Derivates
        {
            class TestComputeBoundaryCurve
            {
            public:
                typedef DIPaCUS::Misc::ComputeBoundaryCurve::Image2D Image2D;
                typedef DIPaCUS::Misc::ComputeBoundaryCurve::Curve Curve;
        
                typedef DGtal::Z2i::KSpace KSpace;
                typedef DGtal::functors::SCellToIncidentPoints<KSpace> AdapterFunctor;
        
                typedef DGtal::ConstRangeAdapter< Curve::ConstIterator,
                        AdapterFunctor,
                        AdapterFunctor::Output > RangeAdapter;
        
                typedef RangeAdapter::ConstCirculator RangeAdapterCirculator;
                typedef DGtal::StabbingCircleComputer<RangeAdapterCirculator> SegmentComputer;
                typedef DGtal::CurvatureFromDCAEstimator<SegmentComputer, false> SCEstimator;
        
            private:
                const std::vector<std::string> imgFilenames = {"square.pgm",
                                                               "square_one_pixel_concavity.pgm",
                                                               "square_potential_hole.pgm",
                                                               "square_shorts.pgm"};
        
                void createCurve(Curve& curve,const Image2D& image);
                void createCurve(Curve& curve, const std::string imgFilename);
        
                double estimateCurvature(Curve& curve , const KSpace& KImage);
        
                void connectivity();
                void afterDilation();
        
            public:
                TestComputeBoundaryCurve();
            };
        }
    }
}
#endif //TEST_DIPACUS_DERIVATES_MISC_H