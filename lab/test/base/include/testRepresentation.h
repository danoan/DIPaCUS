#ifndef TEST_DIPACUS_BASE_REPRESENTATION_H
#define TEST_DIPACUS_BASE_REPRESENTATION_H

#include <string>
#include "DIPaCUS/base/Representation.h"

#include "boost/filesystem.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

using namespace DIPaCUS::Representation;

namespace Test
{
    extern std::string IMAGE_INPUT_PATH;
    extern std::string IMAGE_OUTPUT_PATH;

    extern bool verbose;
    extern bool visualOutput;

    struct Representation {
        typedef DGtal::Z2i::Point Point;

        Representation();
    };
}


#endif //TEST_DIPACUS_BASE_REPRESENTATION_H
