
#include "Representation/testRepresentation.h"

namespace DIPaCUS{ namespace Test{ namespace Representation {

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

    bool Intern::digitalPointsMapsImagePoints(const DigitalSet& ds,
                                              const Image2D& image,
                                              const Point& translation)
    {
        bool flag_ds_assert=true;
        std::for_each(ds.domain().begin(),
                      ds.domain().end(),
                      [&flag_ds_assert,&ds,&image,&translation](Point _p) mutable
                      {
                          Point p = _p + translation;
                          if(ds(_p))
                              flag_ds_assert = flag_ds_assert && image(p) > 0;
                          else
                              flag_ds_assert = flag_ds_assert && image(p) == 0;
                      });

        return flag_ds_assert;
    }

    void Intern::boundingBox(BoundingBox& bb, const Image2D& img)
    {
        DigitalSet ds(img.domain());
        DIPaCUS::Representation::imageAsDigitalSet(ds,img);
        ds.computeBoundingBox(bb.lb,bb.ub);
    }

    void Intern::boundingBox(BoundingBox& bb, const cv::Mat& cvImg)
    {
        Domain domain( Point(0,0),Point(cvImg.cols+1,cvImg.rows+1) );
        DigitalSet ds(domain);

        DIPaCUS::Representation::CVMatToDigitalSet(ds,cvImg);
        ds.computeBoundingBox(bb.lb,bb.ub);
    }

    bool testDigitalSetToImage(const DigitalSet& ds,Logger& logger)
    {
        logger < Logger::HeaderTwo < "Tests DigitalSetAsImage" < Logger::Normal;

        Image2D image(ds.domain());
        DIPaCUS::Representation::digitalSetToImage(image,ds);

        BoundingBox bbImage;
        Intern::boundingBox(bbImage,image);

        BoundingBox bbDs;
        ds.computeBoundingBox(bbDs.lb,bbDs.ub);

        logger < Logger::LoggableObject<Image2D>(image,"ds-to-image.pgm");

        bool t1 = bbImage==bbDs;
        bool t2 = Intern::digitalPointsMapsImagePoints(ds,image,Point(0,0));

        logger < "Passed (bounding-boxes): " < t1 < "\n";
        logger < "Passed (exact-copy): " < t2 < "\n";

        return t1 && t2;
    }

    bool testImageAsDigitalSet(const std::string& imagePath,Logger& logger)
    {
        logger < Logger::HeaderTwo < "Tests ImageAsDigitalSet" < Logger::Normal;

        Image2D image = DGtal::GenericReader<Image2D>::import(imagePath);
        DigitalSet ds(image.domain());
        DIPaCUS::Representation::imageAsDigitalSet(ds, image);

        BoundingBox bbImage;
        Intern::boundingBox(bbImage,image);

        BoundingBox bbDs;
        ds.computeBoundingBox(bbDs.lb,bbDs.ub);

        logger < Logger::LoggableObject<DigitalSet>(ds,"image-to-ds.eps");

        bool t1 = bbDs==bbImage;
        bool t2 = Intern::digitalPointsMapsImagePoints(ds,image,Point(0,0));

        logger < "Passed (bounding-boxes): " < t1 < "\n";
        logger < "Passed (exact-copy): " < t2 < "\n";

        return t1 && t2;
    }

    bool testDigitalSetToCVMat(const DigitalSet& testDS,Logger& logger)
    {
        logger < Logger::HeaderTwo < "Tests DigitalSetToCVMat" < Logger::Normal;

        const Domain& domain = testDS.domain();
        Point dLB = domain.lowerBound();
        Point dimSize = domain.upperBound() - domain.lowerBound() + Point(1,1);

        cv::Mat cvImg = cv::Mat::zeros(dimSize(1),dimSize(0),GRAYSCALE_IMAGE_TYPE);
        DIPaCUS::Representation::digitalSetToCVMat(cvImg,testDS);

        BoundingBox bbDS,bbCV;
        testDS.computeBoundingBox(bbDS.lb,bbDS.ub);
        Intern::boundingBox(bbCV,cvImg);

        Point translation = Point(0,0) - dLB;

        logger < Logger::LoggableObject<cv::Mat>(cvImg,"ds-to-cv.pgm");

        bool t1 = bbCV.ub==bbDS.ub+translation;
        bool t2 = Intern::digitalPointsMapsImagePoints(testDS,cvImg,translation);

        logger < "Passed (bounding-boxes): " < t1 < "\n";
        logger < "Passed (exact-copy): " < t2 < "\n";

        return t1 && t2;

    }

    bool testCVMatToDigitalSet(const std::string& imagePath,Logger& logger)
    {
        logger < Logger::HeaderTwo < "Tests CVMatToDigitalSet" < Logger::Normal;

        cv::Mat cvImg = cv::imread(imagePath,GRAYSCALE_IMAGE_TYPE);
        Domain domain( Point(0,0),Point(cvImg.cols-1,cvImg.rows-1) );

        DigitalSet ds(domain);
        DIPaCUS::Representation::CVMatToDigitalSet(ds,cvImg);

        BoundingBox bbCvImg;
        Intern::boundingBox(bbCvImg,cvImg);

        BoundingBox bbDs;
        ds.computeBoundingBox(bbDs.lb,bbDs.ub);

        logger < Logger::LoggableObject<DigitalSet>(ds,"cv-to-ds.eps");

        bool t1 = bbDs==bbCvImg;
        bool t2 = Intern::digitalPointsMapsImagePoints(ds,cvImg,Point(0,0));

        logger < "Passed (bounding-boxes): " < t1 < "\n";
        logger < "Passed (exact-copy): " < t2 < "\n";

        return t1 && t2;
    }


    bool testImageToCVMat(const std::string& imagePath,Logger& logger)
    {
        logger < Logger::HeaderTwo < "Tests DigitalSetToCVMat" < Logger::Normal;

        Image2D image = DGtal::GenericReader<Image2D>::import(imagePath);

        const Domain& domain = image.domain();
        Point dimSize = domain.upperBound() - domain.lowerBound() + Point(1,1);

        cv::Mat cvImg = cv::Mat::zeros(dimSize(1),dimSize(0),GRAYSCALE_IMAGE_TYPE);
        DIPaCUS::Representation::imageToCVMat(cvImg,image);

        logger < Logger::LoggableObject<cv::Mat>(cvImg,"image-to-cv.pgm");

        BoundingBox bbImg,bbCV;
        Intern::boundingBox(bbImg,image);
        Intern::boundingBox(bbCV,cvImg);

        bool t1 = bbCV.ub==bbImg.ub;

        logger < "Passed (bounding-boxes): " < t1 < "\n";

        return t1;
    }

    bool runTest(std::ostream& os, std::string outputFolder, bool exportObjectsFlag)
    {
        Logger logger(os,outputFolder,exportObjectsFlag);
        logger < Logger::HeaderOne < "Test Representation" < Logger::Normal;

        bool flag=true;

        flag = flag && testDigitalSetToImage(Data::dsSquare,logger);
        flag = flag && testImageAsDigitalSet(Data::giSquare,logger);
        flag = flag && testDigitalSetToCVMat(Data::dsSquare,logger);
        flag = flag && testCVMatToDigitalSet(Data::giSquare,logger);
        flag = flag && testImageToCVMat(Data::giSquare,logger);

        return flag;
    }

}}}



