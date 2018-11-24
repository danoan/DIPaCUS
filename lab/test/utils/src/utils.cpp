#include "utils/utils.h"

using namespace Test;

Utils::DigitalSet Utils::createSquareDS(int sideLength)
{
    double radius = sideLength/2.0*sqrt(2);
    return DIPaCUS::Shapes::square(1.0,0,0,radius);
}

void Utils::boundingBox(BoundingBox& bb,
                                 const Image2D& image)
{
    Intern::ImageAdapter imgBegin = Intern::imageAdapter(image,image.domain().begin(),1);
    Intern::ImageAdapter imgEnd = Intern::imageAdapter(image,image.domain().end(),1);

    Intern::boundingBox(bb,imgBegin,imgEnd);
}

void Utils::boundingBox(BoundingBox& bb,
                                 const cv::Mat& cvImg)
{
    Domain domain(Point(0,0),Point(cvImg.cols-1,cvImg.rows-1) );

    Intern::CVImageAdapter cvImgBegin = Intern::cvImageAdapter(cvImg,domain.begin(),1);
    Intern::CVImageAdapter cvImgEnd = Intern::cvImageAdapter(cvImg,domain.end(),1);

    Intern::boundingBox(bb,cvImgBegin,cvImgEnd);
}

void Utils::computeBoundaryCurve(const DigitalSet &ds,
                                 Curve &curve)
{
    typedef DGtal::Z2i::Domain Domain;
    typedef DGtal::Z2i::KSpace KSpace;

    typedef DIPaCUS::Representation::Image2D Image2D;
    typedef DGtal::Z2i::SCell SCell;
    typedef DGtal::SurfelAdjacency<KSpace::dimension> SurfelAdjacency;
    typedef DGtal::Surfaces<KSpace> Surfaces;
    typedef DGtal::functors::SimpleThresholdForegroundPredicate<Image2D> ThreshPredicate;

    Image2D image(ds.domain());
    DIPaCUS::Representation::digitalSetToImage(image,ds);
    KSpace KImage;

    KImage.init(image.domain().lowerBound(),image.domain().upperBound(),true);

    ThreshPredicate imagePredicate (image,1);
    SCell imageBel = Surfaces::findABel(KImage, imagePredicate, 10000);

    SurfelAdjacency SAdj(true);

    std::vector<SCell> boundarySCells;
    Surfaces::track2DBoundary(boundarySCells,
                              KImage,
                              SAdj,
                              imagePredicate,
                              imageBel);

    curve.initFromSCellsVector(boundarySCells);
}