#include "testMisc.h"

namespace Test
{
    std::string projectDir = std::string(PROJECT_DIR);

    std::string IMAGE_INPUT_PATH = projectDir + "/input_images";
    std::string IMAGE_OUTPUT_PATH = projectDir + "/output_images";

    bool verbose  = true;
    bool visualOutput = false;
}

int main()
{
    std::cout << "Test ComputeBoundaryCurve" << std::endl;
    Test::TestComputeBoundaryCurve();
    return 0;
}