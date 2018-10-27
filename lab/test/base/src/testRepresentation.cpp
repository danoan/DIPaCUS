#include <DGtal/io/writers/GenericWriter.h>
#include "testRepresentation.h"

namespace Test
{
    Representation::Representation()
    {
        int IMAGE_TYPE = CV_8UC1;
        std::string visualOutputDir = IMAGE_OUTPUT_PATH + "/Representation";

        if(verbose) std::cout << "Tests ImageAsDigitalSet" << std::endl;

        //Expected number of white pixels: 13x13 square -> 169 pixels
        boost::filesystem::path p(IMAGE_INPUT_PATH);
        p /= "square.pgm";

        Image2D image = DGtal::GenericReader<Image2D>::import(p.generic_string());
        DigitalSet ds(image.domain());
        imageAsDigitalSet(ds, image);

        assert(ds.size() == 169);

        if(verbose) std::cout << "Tests DigitalSetToCVMat; CVMatToDigitalSet" << std::endl;

        //DigitalSetAsImage
        Point pl = image.domain().lowerBound();
        Point pu = image.domain().upperBound();

        unsigned long int rows = (pu-pl)[1];
        unsigned long int cols = (pu-pl)[0];

        cv::Mat cvImg(rows,cols,IMAGE_TYPE);
        digitalSetToCVMat(cvImg,ds);

        DigitalSet ds2(image.domain());
        CVMatToDigitalSet(ds2,cvImg);

        bool flag_ds_assert=true;
        std::for_each(ds.begin(),
                      ds.end(),
                      [flag_ds_assert,ds2](auto it) mutable{
                          flag_ds_assert = flag_ds_assert && ds2.find(it)!=ds2.end();
                      });
        assert(flag_ds_assert==true);


        if(verbose) std::cout << "Tests CVMatToImage; DigitalSetToCVMat" << std::endl;

        cv::Mat cvImg2(rows,cols,IMAGE_TYPE);
        digitalSetToCVMat(cvImg2,ds2);

        Image2D image2(image.domain());
        CVMatToImage(image2,cvImg2);

        if(visualOutput)
        {
            DGtal::GenericWriter<Image2D>::exportFile(visualOutputDir + "/img.pgm", image);
            DGtal::GenericWriter<Image2D>::exportFile(visualOutputDir + "/img2.pgm", image2);
        }
        assert(image==image2);
    }
}