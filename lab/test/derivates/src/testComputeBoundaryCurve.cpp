#include <DGtal/io/readers/GenericReader.h>
#include "testComputeBoundaryCurve.h"

using namespace DIPaCUS::Test::Derivates;

void TestComputeBoundaryCurve::createCurve(Curve& curve,
                                           const Image2D& image)
{
    DIPaCUS::Misc::ComputeBoundaryCurve(image,curve,100);
}

void TestComputeBoundaryCurve::createCurve(Curve& curve,
                                           const std::string imgFilename)
{
    std::string imgFilepath = IMAGE_INPUT_PATH + "/" + imgFilename;
    Image2D image = DGtal::GenericReader<Image2D>::import(imgFilepath);

    createCurve(curve,image);
}

double TestComputeBoundaryCurve::estimateCurvature(Curve &curve, const KSpace& KImage)
{
    AdapterFunctor af(KImage);
    RangeAdapter range(curve.begin(),
                       curve.end(),
                       af);

    SegmentComputer sc;
    SCEstimator f;

    DGtal::MostCenteredMaximalSegmentEstimator<SegmentComputer,SCEstimator> MCMDCACurvatureEstimator(sc,f);

    std::vector<double> estimations;

    MCMDCACurvatureEstimator.init(1.0,range.c(),range.c());
    MCMDCACurvatureEstimator.eval(range.c(),range.c(),std::back_inserter(estimations));

    double curvSum = 0;
    std::for_each(estimations.begin(),estimations.end(),[&curvSum](const double &v) mutable{curvSum+=v;});

    return curvSum;
}

void TestComputeBoundaryCurve::connectivity()
{
    for(auto it = imgFilenames.begin();it!=imgFilenames.end();++it)
    {
        if(verbose) std::cout << "Test for image: " << *it << std::endl;

        Curve curve;
        createCurve(curve,*it);

        assert(curve.isValid());
        assert(curve.isClosed());
    }
}

void TestComputeBoundaryCurve::afterDilation()
{
    for(auto it = imgFilenames.begin();it!=imgFilenames.end();++it)
    {
        if (verbose) std::cout << "Test for image: " << *it << std::endl;

        std::string imgFilepath = IMAGE_INPUT_PATH + "/" + *it;
        Image2D original = DGtal::GenericReader<Image2D>::import(imgFilepath);

        DIPaCUS::Representation::DigitalSet originalDS(original.domain());
        DIPaCUS::Representation::imageAsDigitalSet(originalDS,original);

        Image2D dilation(original.domain());

        typedef DIPaCUS::Morphology::StructuringElement SE;
        SE se(SE::RECT,1);
        DIPaCUS::Morphology::dilate(dilation,originalDS,se);

        Curve curve;
        createCurve(curve,dilation);

        assert(curve.isValid());
        assert(curve.isClosed());

        KSpace KImage;
        KImage.init(dilation.domain().lowerBound(),
                    dilation.domain().upperBound(),
                    true);

        if(visualOutput)
        {
            DGtal::Board2D board;
            board << curve;
            board.saveEPS( std::string(IMAGE_OUTPUT_PATH + "/" + *it + ".eps").c_str() );
        }

        if(verbose) std::cout << "Curvature summation: " << estimateCurvature(curve,KImage) << std::endl;
    }
}

TestComputeBoundaryCurve::TestComputeBoundaryCurve() 
{
    if(verbose) std::cout << "***Testing connectivity***" << std::endl;
    connectivity();

    if(verbose) std::cout << "***Testing afterDilation***" << std::endl;
    afterDilation();

}