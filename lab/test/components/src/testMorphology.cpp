#include <data.h>
#include "testMorphology.h"

namespace Test{

    bool Morphology::equalBoundingBoxes(const DigitalSet& ds1,
                                        const DigitalSet& ds2)
    {
        Point lbDS1,ubDS1,lbDS2,ubDS2;
        ds1.computeBoundingBox(lbDS1,ubDS1);
        ds2.computeBoundingBox(lbDS2,ubDS2);

        return lbDS1==lbDS2 && ubDS1==ubDS2;
    }

    void Morphology::testDilate(int iterations,
                                int elementSize,
                                const DigitalSet& dsInput,
                                const DigitalSet& dsCompare)
    {
        Point expandingPoint( iterations*elementSize,iterations*elementSize );
        Domain dilatedDomain(dsInput.domain().lowerBound() - expandingPoint,
                             dsInput.domain().upperBound() + expandingPoint);

        DigitalSet dilatedDS(dilatedDomain);

        DIPaCUS::Morphology::StructuringElement se(DIPaCUS::Morphology::StructuringElement::RECT,elementSize);
        DIPaCUS::Morphology::dilate(dilatedDS,dsInput,se,iterations);

        assert(dilatedDS.size()==dsCompare.size());
        assert(equalBoundingBoxes(dilatedDS,dsCompare));
    }


    void Morphology::testErosion(int iterations,
                                int elementSize,
                                const DigitalSet& dsInput,
                                const DigitalSet& dsCompare)
    {
        DigitalSet erodedDS(dsInput.domain());

        DIPaCUS::Morphology::StructuringElement se(DIPaCUS::Morphology::StructuringElement::RECT,elementSize);
        DIPaCUS::Morphology::erode(erodedDS,dsInput,se,iterations);

        assert(erodedDS.size()==dsCompare.size());
        assert(equalBoundingBoxes(erodedDS,dsCompare));
    }


    void Morphology::testOpening(int iterations,
                                 int elementSize,
                                 const DigitalSet& dsInput)
    {
        DigitalSet dsOut(dsInput.domain());

        DIPaCUS::Morphology::StructuringElement se(DIPaCUS::Morphology::StructuringElement::RECT,elementSize);
        DIPaCUS::Morphology::opening(dsOut,dsInput,se,iterations);

        assert(dsOut.size()==dsInput.size());
        assert(equalBoundingBoxes(dsOut,dsInput));
    }

    void Morphology::testClosing(int iterations,
                                 int elementSize,
                                 const DigitalSet& dsInput)
    {
        Point expandingPoint( iterations*elementSize,iterations*elementSize );
        Domain dilatedDomain(dsInput.domain().lowerBound() - expandingPoint,
                             dsInput.domain().upperBound() + expandingPoint);

        DigitalSet dsOut(dilatedDomain);

        DIPaCUS::Morphology::StructuringElement se(DIPaCUS::Morphology::StructuringElement::RECT,elementSize);
        DIPaCUS::Morphology::closing(dsOut,dsInput,se,iterations);

        assert(dsOut.size()==dsInput.size());
        assert(equalBoundingBoxes(dsOut,dsInput));
    }
}