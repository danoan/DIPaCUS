#include "DIPaCUS/components/Transform.h"

using namespace DIPaCUS;

void Transform::resize(Image2D &out,
                       const Image2D &input,
                       double factor)
{
    Point dimSizeIn = input.domain().upperBound() - input.domain().lowerBound() + Point(1,1);
    Point dimSizeOut = out.domain().upperBound() - out.domain().lowerBound() + Point(1,1);

    assert(dimSizeOut>=dimSizeIn*factor);

    cv::Mat cvInput(dimSizeIn(1), dimSizeIn(0), IMG_TYPE);
    cv::Mat cvOut(dimSizeOut(1), dimSizeOut(0), IMG_TYPE);


    DIPaCUS::Representation::imageToCVMat(cvInput, input);
    cv::resize(cvInput, cvOut, cvOut.size(), factor, factor, cv::INTER_NEAREST);
    DIPaCUS::Representation::CVMatToImage(out, cvOut);
}


void Transform::invertColors(Image2D &outputImage,
                             const Image2D &inputImage)
{
    Point dimSizeIn = inputImage.domain().upperBound() - inputImage.domain().lowerBound() + Point(1,1);
    Point dimSizeOut = outputImage.domain().upperBound() - outputImage.domain().lowerBound() + Point(1,1);

    assert(dimSizeOut>=dimSizeIn);

    cv::Mat cvOut(dimSizeOut(1), dimSizeOut(0), IMG_TYPE);

    DIPaCUS::Representation::imageToCVMat(cvOut, inputImage);

    auto begin = cvOut.begin<unsigned char>();
    auto end = cvOut.end<unsigned char>();
    for (auto it = begin; it != end; ++it) {
        *it = *it == 255 ? 0 : 255;
    }

    DIPaCUS::Representation::CVMatToImage(outputImage, cvOut);
}

void Transform::addBorder(Image2D &outputImage,
                          const Image2D &inputImage,
                          int borderWidth)
{
    Point dimSizeIn = inputImage.domain().upperBound() - inputImage.domain().lowerBound() + Point(1,1);
    Point dimSizeOut = outputImage.domain().upperBound() - outputImage.domain().lowerBound() + Point(1,1);

    assert(dimSizeOut>=dimSizeIn+Point(borderWidth,borderWidth)*2);


    cv::Mat cvOut(dimSizeIn(1), dimSizeIn(0), IMG_TYPE); //sizeIn because copyMakeBorder changes cv::Mat size
    DIPaCUS::Representation::imageToCVMat(cvOut,
                                          inputImage);

    cv::copyMakeBorder(cvOut, cvOut, borderWidth, borderWidth, borderWidth, borderWidth,
                       CV_HAL_BORDER_CONSTANT, 0);

    DIPaCUS::Representation::CVMatToImage(outputImage,
                                          cvOut);
}


void Transform::eliminateLoops(Curve &curveOut,
                               const KSpace &KImage,
                               const Curve &curveIn)
{
    std::vector<KSpace::SCell> vectorOfSCell;

    std::map<KSpace::SCell, KSpace::SCell> visited;
    KSpace::SCell toReconnectSCell;

    int i = 0;
    for (auto it = curveIn.begin(); it != curveIn.end(); ++it, ++i)
    {
        KSpace::SCell pointel = KImage.sDirectIncident(*it, *KImage.sDirs(*it));
        if (visited.find(pointel) == visited.end())
        {
            visited[pointel] = *it;
            vectorOfSCell.push_back(*it);
        }
        else
        {
            toReconnectSCell = visited[pointel];

            KSpace::SCell backOfVector = vectorOfSCell.back();
            while (backOfVector != toReconnectSCell)
            {
                vectorOfSCell.pop_back();
                backOfVector = vectorOfSCell.back();
            }
        }
    }

    curveOut.initFromSCellsVector(vectorOfSCell);
}

DGtal::Z2i::DigitalSet Transform::bottomLeftBoundingBoxAtOrigin(const DGtal::Z2i::DigitalSet& ds,
                                                                const DGtal::Z2i::Point border)
{
    assert(ds.size()>0);

    Point lb,ub;
    ds.computeBoundingBox(lb,ub);

    Point diff = lb;

    Domain newDomain( Point(0,0),ub - diff + 2*border );
    DigitalSet newDS(newDomain);
    for(auto it=ds.begin();it!=ds.end();++it)
    {
        newDS.insert(*it - diff + border);
    }

    return newDS;
}