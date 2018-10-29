
#include "Representation/testRepresentation.h"

using namespace Representation;

void Representation::runTest()
{
    std::string visualOutputDir = IMAGE_OUTPUT_PATH + "/Representation";

    Intern::testDigitalSetToImage(Data::dsSquare);
    Intern::testImageAsDigitalSet(Data::giSquare);
    Intern::testDigitalSetToCVMat(Data::dsSquare);
    Intern::testCVMatToDigitalSet(Data::giSquare);
    Intern::testImageToCVMat(Data::giSquare);

}

using namespace Test::Representation;

bool Intern::digitalPointsMapsImagePoints(const DigitalSet& ds,
                                          const cv::Mat& cvImg,
                                          const Point& translation)
{
    const int rows = cvImg.rows-1;
    bool flag_ds_assert=true;
    std::for_each(ds.domain().begin(),
                  ds.domain().end(),
                  [&flag_ds_assert,&ds,&cvImg,&translation,&rows](Point _p) mutable
                  {
                      Point p = _p + translation;
                      if(ds(_p))
                          flag_ds_assert = flag_ds_assert && cvImg.at<unsigned char>(rows-p(1),p(0)) > 0;
                      else
                          flag_ds_assert = flag_ds_assert && cvImg.at<unsigned char>(rows-p(1),p(0)) == 0;
                  });

    return flag_ds_assert;
}

void Intern::testDigitalSetToImage(const DigitalSet& ds)
{
    std::cout << "Tests DigitalSetAsImage" << std::endl;

    Image2D image(ds.domain());
    DIPaCUS::Representation::digitalSetToImage(image,ds);

    BoundingBox bbImage;
    boundingBox(bbImage,image);

    BoundingBox bbDs;
    ds.computeBoundingBox(bbDs.lb,bbDs.ub);

    assert(bbImage==bbDs);
}

void Intern::testImageAsDigitalSet(const GrayscaleImageInstance& gii)
{
    std::cout << "Tests ImageAsDigitalSet" << std::endl;

    Image2D image = DGtal::GenericReader<Image2D>::import(gii.imagePath);
    DigitalSet ds(image.domain());
    imageAsDigitalSet(ds, image);

    BoundingBox bbImage;
    boundingBox(bbImage,image);

    BoundingBox bbDs;
    ds.computeBoundingBox(bbDs.lb,bbDs.ub);

    assert(bbDs==bbImage);
    assert(ds.size() == gii.totalPixels);
}

void Intern::testDigitalSetToCVMat(const DigitalSet& testDS)
{
    if(verbose) std::cout << "Tests DigitalSetToCVMat" << std::endl;

    const Domain& domain = testDS.domain();
    Point dLB = domain.lowerBound();
    Point dimSize = domain.upperBound() - domain.lowerBound() + Point(1,1);

    cv::Mat cvImg = cv::Mat::zeros(dimSize(1),dimSize(0),GRAYSCALE_IMAGE_TYPE);
    digitalSetToCVMat(cvImg,testDS);

    BoundingBox bbDS,bbCV;
    testDS.computeBoundingBox(bbDS.lb,bbDS.ub);
    boundingBox(bbCV,cvImg);

    Point translation = Point(0,0) - dLB;

    assert(bbCV.ub==bbDS.ub+translation);
    assert(digitalPointsMapsImagePoints(testDS,cvImg,translation) );

}

void Intern::testCVMatToDigitalSet(const GrayscaleImageInstance& gii)
{
    std::cout << "Tests CVMatToDigitalSet" << std::endl;

    cv::Mat cvImg = cv::imread(gii.imagePath,GRAYSCALE_IMAGE_TYPE);
    Domain domain( Point(0,0),Point(cvImg.cols-1,cvImg.rows-1) );

    DigitalSet ds(domain);
    DIPaCUS::Representation::CVMatToDigitalSet(ds,cvImg);

    BoundingBox bbCvImg;
    boundingBox(bbCvImg,cvImg);

    BoundingBox bbDs;
    ds.computeBoundingBox(bbDs.lb,bbDs.ub);

    assert(bbDs==bbCvImg);
    assert(ds.size() == gii.totalPixels);
    assert(digitalPointsMapsImagePoints(ds,cvImg,Point(0,0)));
}


void Intern::testImageToCVMat(const GrayscaleImageInstance& gii)
{
    if(verbose) std::cout << "Tests DigitalSetToCVMat" << std::endl;

    Image2D image = DGtal::GenericReader<Image2D>::import(gii.imagePath);

    const Domain& domain = image.domain();
    Point dLB = domain.lowerBound();
    Point dimSize = domain.upperBound() - domain.lowerBound() + Point(1,1);

    cv::Mat cvImg = cv::Mat::zeros(dimSize(1),dimSize(0),GRAYSCALE_IMAGE_TYPE);
    imageToCVMat(cvImg,image);

    DGtal::GenericWriter<Image2D>::exportFile("/home/daniel/image2D.pgm",image);

    BoundingBox bbImg,bbCV;
    boundingBox(bbImg,image);
    boundingBox(bbCV,cvImg);

    Point translation = Point(0,0) - dLB;

    assert(bbCV.ub==bbImg.ub+translation);
}
