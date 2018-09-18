#ifndef DIPACUS_TESTFILLINTERIOR_H
#define DIPACUS_TESTFILLINTERIOR_H

#include <DIPaCUS/derivates/Misc.h>

#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/shapes/GaussDigitizer.h>
#include <DGtal/shapes/parametric/Ball2D.h>
#include <DGtal/topology/SurfelAdjacency.h>
#include <DGtal/topology/helpers/Surfaces.h>

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
            class TestCompactSetFromClosedCurve
            {
            public:
                typedef DGtal::Z2i::KSpace KSpace;
                typedef DGtal::Z2i::Space Space;
                typedef DGtal::Z2i::Domain Domain;
                typedef DGtal::Z2i::DigitalSet DigitalSet;
                
                
                typedef DGtal::Ball2D<Space> EuclideanBall2D;
                typedef DGtal::GaussDigitizer<Space,EuclideanBall2D> DigitalBall;

                typedef DGtal::SurfelAdjacency<KSpace::dimension> SurfelAdjacency;
                typedef DGtal::Surfaces<KSpace> Surfaces;

                typedef DGtal::Z2i::Curve Curve;
                typedef Curve::SCell SCell;
                typedef Curve::Point Point;



                TestCompactSetFromClosedCurve();
            };
        }
    }
}

#endif //DIPACUS_TESTFILLINTERIOR_H
