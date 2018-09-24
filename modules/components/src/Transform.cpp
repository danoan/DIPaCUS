#include "DIPaCUS/components/Transform.h"

using namespace DIPaCUS::Transform;



Resize::Resize(Image2D &input,
               Image2D &out,
               double factor)
{
    int rIn = input.domain().upperBound()[1] + 1;
    int cIn = input.domain().upperBound()[0] + 1;

    int rOut = out.domain().upperBound()[1] + 1;
    int cOut = out.domain().upperBound()[0] + 1;

    cv::Mat cvInput(rIn, cIn, IMG_TYPE);
    cv::Mat cvOut(rOut, cOut, IMG_TYPE);

    DIPaCUS::Representation::ImageToCVMat(cvInput, input);
    cv::resize(cvInput, cvOut, cvOut.size(), factor, factor, cv::INTER_NEAREST);
    DIPaCUS::Representation::CVMatToImage(out, cvOut);
}


InvertColors::InvertColors(Image2D &outputImage, Image2D &inputImage)
{
    int r = inputImage.domain().upperBound()[1] + 1;
    int c = inputImage.domain().upperBound()[0] + 1;

    cv::Mat cvIn(r, c, IMG_TYPE);

    DIPaCUS::Representation::ImageToCVMat(cvIn, inputImage);

    auto begin = cvIn.begin<unsigned char>();
    auto end = cvIn.end<unsigned char>();
    for (auto it = begin; it != end; ++it) {
        *it = *it == 255 ? 0 : 255;
    }

    DIPaCUS::Representation::CVMatToImage(outputImage, cvIn);
}

AddBorder::AddBorder(Image2D &outputImage,
                     Image2D &inputImage,
                     int borderWidth)
{
    int r = inputImage.domain().upperBound()[1] + 1;
    int c = inputImage.domain().upperBound()[0] + 1;

    cv::Mat cvIn(r, c, IMG_TYPE);

    DIPaCUS::Representation::ImageToCVMat(cvIn,
                                          inputImage);

    cv::copyMakeBorder(cvIn, cvIn, borderWidth, borderWidth, borderWidth, borderWidth,
                       CV_HAL_BORDER_CONSTANT, 0);

    DIPaCUS::Representation::CVMatToImage(outputImage,
                                          cvIn);
}


EliminateLoops::EliminateLoops(Curve &curveOut,
                               KSpace &KImage,
                               Curve &curveIn)
{
    std::vector<KSpace::SCell> vectorOfSCell;

    std::map<KSpace::SCell, KSpace::SCell> appearanceTable;
    KSpace::SCell toReconnectSCell;

    int i = 0;
    for (auto it = curveIn.begin(); it != curveIn.end(); ++it, ++i) {
        KSpace::SCell pointel = KImage.sDirectIncident(*it, *KImage.sDirs(*it));
        if (appearanceTable.find(pointel) == appearanceTable.end()) {
            appearanceTable[pointel] = *it;
            vectorOfSCell.push_back(*it);
        } else {
            toReconnectSCell = appearanceTable[pointel];

            KSpace::SCell backOfVector = vectorOfSCell.back();
            while (backOfVector != toReconnectSCell) {
                vectorOfSCell.pop_back();
                backOfVector = vectorOfSCell.back();
            }
        }
    }

    curveOut.initFromSCellsVector(vectorOfSCell);
}

namespace DIPaCUS
{
    namespace Transform
    {
        DGtal::Z2i::DigitalSet CenterDigitalSetAtOrigin(const DGtal::Z2i::DigitalSet& ds)
        {
            using namespace DGtal::Z2i;
            assert(ds.size()>0);
            Point lb,ub;
            ds.computeBoundingBox(lb,ub);

            Point diff = lb;
            Domain newDomain( Point(-2,-2),ub - diff + Point(2,2) );
            DigitalSet newDS(newDomain);
            for(auto it=ds.begin();it!=ds.end();++it)
            {
                newDS.insert(*it - diff);
            }

            return newDS;

        }
    }
}
