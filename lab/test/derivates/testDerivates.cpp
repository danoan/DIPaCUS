#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "testComputeBoundaryCurve.h"
#include "testCompactSetFromClosedCurve.h"

namespace DIPaCUS
{
    namespace Test
    {
        std::string projectDir = std::string(PROJECT_DIR);

        std::string IMAGE_INPUT_PATH = projectDir + "/input_images";
        std::string IMAGE_OUTPUT_PATH = projectDir + "/output_images";

        bool verbose  = true;
        bool visualOutput = true;
    }
}

using namespace DIPaCUS::Test;

int main()
{
    std::cout << "Project Directory: " << projectDir << std::endl;
    boost::filesystem::path p (IMAGE_OUTPUT_PATH);
    boost::filesystem::create_directories(p);

    std::cout << "Test ComputeBoundaryCurve" << std::endl;
    Derivates::TestComputeBoundaryCurve();

    std::cout << "Test CompactSetFromClosedCurve" << std::endl;
    Derivates::TestCompactSetFromClosedCurve();
    return 0;
}