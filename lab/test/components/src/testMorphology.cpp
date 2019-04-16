#include <data.h>
#include "testMorphology.h"

namespace DIPaCUS{ namespace Test{

    bool Morphology::equalBoundingBoxes(const DigitalSet& ds1,
                                        const DigitalSet& ds2)
    {
        Point lbDS1,ubDS1,lbDS2,ubDS2;
        ds1.computeBoundingBox(lbDS1,ubDS1);
        ds2.computeBoundingBox(lbDS2,ubDS2);

        return lbDS1==lbDS2 && ubDS1==ubDS2;
    }

    bool Morphology::testDilate(int iterations,
                                int elementSize,
                                const DigitalSet& dsInput,
                                const DigitalSet& dsCompare,
                                Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test Dilate" < Logger::Normal;
        logger < "iterations: " < iterations < "\nelementSize: " < elementSize < "\n";


        Point expandingPoint( iterations*elementSize,iterations*elementSize );
        Domain dilatedDomain(dsInput.domain().lowerBound() - expandingPoint,
                             dsInput.domain().upperBound() + expandingPoint);

        DigitalSet dilatedDS(dilatedDomain);

        DIPaCUS::Morphology::StructuringElement se(DIPaCUS::Morphology::StructuringElement::RECT,elementSize);
        DIPaCUS::Morphology::dilate(dilatedDS,dsInput,se,iterations);

        logger-"dsInput"-"it"-iterations-"elSize"-elementSize^".eps";
        logger < Logger::LoggableObject<DigitalSet>(dsInput,logger.buffer());

        logger-"dilatedDs"-"it"-iterations-"elSize"-elementSize^".eps";
        logger < Logger::LoggableObject<DigitalSet>(dilatedDS,logger.buffer());

        bool t1 = dilatedDS.size()==dsCompare.size();
        bool t2 = equalBoundingBoxes(dilatedDS,dsCompare);

        logger < "Passed: " < t1 < "\n";
        logger < "Passed: " < t2 < "\n";

        return t1 && t2;
    }


    bool Morphology::testErosion(int iterations,
                                int elementSize,
                                const DigitalSet& dsInput,
                                const DigitalSet& dsCompare,
                                 Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test Erosion" < Logger::Normal;
        logger < "iterations: " < iterations < "\nelementSize: " < elementSize < "\n";

        DigitalSet erodedDS(dsInput.domain());

        DIPaCUS::Morphology::StructuringElement se(DIPaCUS::Morphology::StructuringElement::RECT,elementSize);
        DIPaCUS::Morphology::erode(erodedDS,dsInput,se,iterations);

        logger-"dsInput"-"it"-iterations-"elSize"-elementSize^".eps";
        logger < Logger::LoggableObject<DigitalSet>(dsInput,logger.buffer());

        logger-"erodedDs"-"it"-iterations-"elSize"-elementSize^".eps";
        logger < Logger::LoggableObject<DigitalSet>(erodedDS,logger.buffer());

        bool t1 = erodedDS.size()==dsCompare.size();
        bool t2 = equalBoundingBoxes(erodedDS,dsCompare);

        logger < "Passed: " < t1 < "\n";
        logger < "Passed: " < t2 < "\n";

        return t1 && t2;
    }


    bool Morphology::testOpening(int iterations,
                                 int elementSize,
                                 const DigitalSet& dsInput,
                                 Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test Opening" < Logger::Normal;
        logger < "iterations: " < iterations < "\nelementSize: " < elementSize < "\n";

        DigitalSet dsOut(dsInput.domain());

        DIPaCUS::Morphology::StructuringElement se(DIPaCUS::Morphology::StructuringElement::RECT,elementSize);
        DIPaCUS::Morphology::opening(dsOut,dsInput,se,iterations);

        logger-"dsInput"-"it"-iterations-"elSize"-elementSize^".eps";
        logger < Logger::LoggableObject<DigitalSet>(dsInput,logger.buffer());

        logger-"openedDs"-"it"-iterations-"elSize"-elementSize^".eps";
        logger < Logger::LoggableObject<DigitalSet>(dsOut,logger.buffer());

        bool t1 = dsOut.size()==dsInput.size();
        bool t2 = equalBoundingBoxes(dsOut,dsInput);

        logger < "Passed: " < t1 < "\n";
        logger < "Passed: " < t2 < "\n";

        return t1 & t2;
    }

    bool Morphology::testClosing(int iterations,
                                 int elementSize,
                                 const DigitalSet& dsInput,
                                 Logger& logger)
    {
        logger < Logger::HeaderTwo < "Test Closing" < Logger::Normal;
        logger < "iterations: " < iterations < "\nelementSize: " < elementSize < "\n";

        Point expandingPoint( iterations*elementSize,iterations*elementSize );
        Domain dilatedDomain(dsInput.domain().lowerBound() - expandingPoint,
                             dsInput.domain().upperBound() + expandingPoint);

        DigitalSet dsOut(dilatedDomain);

        DIPaCUS::Morphology::StructuringElement se(DIPaCUS::Morphology::StructuringElement::RECT,elementSize);
        DIPaCUS::Morphology::closing(dsOut,dsInput,se,iterations);

        logger-"dsInput"-"it"-iterations-"elSize"-elementSize^".eps";
        logger < Logger::LoggableObject<DigitalSet>(dsInput,logger.buffer());

        logger-"closedDs"-"it"-iterations-"elSize"-elementSize^".eps";
        logger < Logger::LoggableObject<DigitalSet>(dsOut,logger.buffer());

        bool t1 = dsOut.size()==dsInput.size();
        bool t2 = equalBoundingBoxes(dsOut,dsInput);

        logger < "Passed: " < t1 < "\n";
        logger < "Passed: " < t2 < "\n";

        return t1 & t2;
    }

    bool Morphology::runTest(std::ostream& os, const std::string& outputFolder, bool exportObjects)
    {
        Logger logger(os,outputFolder + "/dilation",exportObjects);
        logger < Logger::HeaderOne < "Morphology Tests" < Logger::Normal;

        bool flag=true;

        flag = flag && testDilate(1,1,Test::Morphology::Data::square11DS,Test::Morphology::Data::square13DS,logger);
        flag = flag && testDilate(2,1,Test::Morphology::Data::square9DS,Test::Morphology::Data::square13DS,logger);
        flag = flag && testDilate(1,2,Test::Morphology::Data::square9DS,Test::Morphology::Data::square13DS,logger);

        logger.changeOutputFolder(outputFolder + "/erosion");

        testErosion(1,1,Test::Morphology::Data::square11DS,Test::Morphology::Data::square9DS,logger);
        testErosion(2,1,Test::Morphology::Data::square13DS,Test::Morphology::Data::square9DS,logger);
        testErosion(1,2,Test::Morphology::Data::square13DS,Test::Morphology::Data::square9DS,logger);

        logger.changeOutputFolder(outputFolder + "/opening");

        testOpening(1,1,Test::Morphology::Data::square11DS,logger);
        testOpening(2,1,Test::Morphology::Data::square11DS,logger);
        testOpening(1,2,Test::Morphology::Data::square11DS,logger);
        testOpening(1,5,Test::Morphology::Data::square11DS,logger);

        logger.changeOutputFolder(outputFolder + "/closing");

        testClosing(1,1,Test::Morphology::Data::square11DS,logger);
        testClosing(2,1,Test::Morphology::Data::square11DS,logger);
        testClosing(1,2,Test::Morphology::Data::square11DS,logger);
        testClosing(1,5,Test::Morphology::Data::square11DS,logger);

        return flag;
    }
}}