#include <DIPaCUS/components/Properties.h>
#include "DIPaCUS/derivates/Misc.h"

using  namespace DIPaCUS::Misc;

DigitalBallIntersection::DigitalBallIntersection(Radius r,
                                                 const DigitalSet &intersectWith) : _r(r),
                                                                                    _ds(intersectWith)
{}

void DigitalBallIntersection::operator()(DigitalSet &intersectionSet,
                                         Point center)
{
    DigitalSet db(intersectionSet.domain());
    digitalBall(db, center, _r);
    DIPaCUS::SetOperations::setIntersection(intersectionSet, db, _ds);
}

void DigitalBallIntersection::digitalBall(DigitalSet &db,
                                          Point center,
                                          int radius)
{
    EuclideanBall eb(center, radius);
    DGtal::Shapes<Domain>::euclideanShaper(db, eb, 1);
}



FindIPNIS::FindIPNIS(Point &ipnil,
                     const DigitalSet &inputSet,
                     const DigitalSet &invalidSet)
{
    DigitalSetIterator it = inputSet.begin();
    for (; it != inputSet.end(); ++it) {
        if (invalidSet.find(*it) == invalidSet.end()) break;
    }

    ipnil = *it;
}


FillInterior::FillInterior(DigitalSet &simplyConnectedSet,
                           const Point &interiorPoint,
                           const DigitalSet &boundary)
{
    simplyConnectedSet.insert(boundary.begin(), boundary.end());

    Point currentPoint, candidatePoint;
    Point neighborFilter[4] = {Point(1, 0), Point(-1, 0), Point(0, 1), Point(0, -1)};

    std::stack<Point> toVisit;

    toVisit.push(interiorPoint);
    while (!toVisit.empty()) {
        currentPoint = toVisit.top();
        simplyConnectedSet.insert(currentPoint);
        toVisit.pop();

        for (int i = 0; i < 4; ++i) {
            candidatePoint = currentPoint + neighborFilter[i];
            if (simplyConnectedSet.find(candidatePoint) != simplyConnectedSet.end()) continue;
            toVisit.push(candidatePoint);
        }
    }
}


NoHoles::NoHoles(DigitalSet &noHoles,
                 const DigitalSet &dsIn)
{
    Domain domain = dsIn.domain();

    DigitalSet boundary(dsIn.domain());
    FourBoundary fb(boundary, dsIn);

    Point interiorPoint;
    FindIPNIS(interiorPoint, dsIn, boundary);

    FillInterior(noHoles, interiorPoint, boundary);
}


ThickBorder::ThickBorder(DigitalSet &thickBorder, const DigitalSet &dsIn, int thickness) {
    Domain domain = dsIn.domain();

    DigitalSet eroded(domain);
    Morphology::erode(eroded,
                      dsIn,
                      Morphology::StructuringElement(Morphology::StructuringElement::RECT,
                                                                   thickness) );

    DIPaCUS::SetOperations::setDifference(thickBorder, dsIn, eroded);
}

ComputeBoundaryCurve::ComputeBoundaryCurve(const Image2D &image,
                                           Curve &boundCurve,
                                           unsigned int thresh_value)
{
    Domain imageDomain = image.domain();
    KSpace KImage;

    KImage.init(imageDomain.lowerBound(),imageDomain.upperBound(),true);

    ThreshPredicate imagePredicate (image,thresh_value);
    SCell imageBel = Surfaces::findABel(KImage, imagePredicate, 10000);

    SurfelAdjacency SAdj(true);

    std::vector<SCell> boundarySCells;
    Surfaces::track2DBoundary(boundarySCells,
                              KImage,
                              SAdj,
                              imagePredicate,
                              imageBel);

    boundCurve.initFromSCellsVector(boundarySCells);

    DIPaCUS::Transform::eliminateLoops(boundCurve,KImage,boundCurve);
}

ComputeBoundaryCurve::ComputeBoundaryCurve(const Image2D& image,
                                           Curve& boundCurve,
                                           unsigned int thresh_value,
                                           SCell imageBel)
{
    Domain imageDomain = image.domain();
    KSpace KImage;

    KImage.init(imageDomain.lowerBound(),imageDomain.upperBound(),true);

    ThreshPredicate imagePredicate (image,thresh_value);

    SurfelAdjacency SAdj(true);

    std::vector<SCell> boundarySCells;
    Surfaces::track2DBoundary(boundarySCells,
                              KImage,
                              SAdj,
                              imagePredicate,
                              imageBel);

    boundCurve.initFromSCellsVector(boundarySCells);

}



ComputeBoundaryCurve::ComputeBoundaryCurve(const DigitalSet& ds,
                                           Curve& boundCurve)
{
    typedef DGtal::Surfaces<KSpace> Surfaces;
    typedef DGtal::SurfelAdjacency<2> SurfelAdjacency;

    const Domain &domain = ds.domain();
    KSpace KImage;

    KImage.init(domain.lowerBound(),domain.upperBound(),true);

    DGtal::Z2i::SCell imageBel = Surfaces::findABel(KImage, ds, 10000);

    SurfelAdjacency SAdj(true);

    std::vector<DGtal::Z2i::SCell> boundarySCells;
    Surfaces::track2DBoundary(boundarySCells,
                              KImage,
                              SAdj,
                              ds,
                              imageBel);

    boundCurve.initFromSCellsVector(boundarySCells);

    DIPaCUS::Transform::eliminateLoops(boundCurve,KImage,boundCurve);
}