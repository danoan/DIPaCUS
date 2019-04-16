#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "testMisc.h"

namespace DIPaCUS
{
    namespace Test
    {
        std::string projectDir = std::string(PROJECT_DIR);
        std::string IMAGE_INPUT_PATH = projectDir + "/input_images";
    }
}

struct InputData
{
    InputData()
    {
        outputFolder="";
        exportObjectsFlag=false;
    }

    std::string outputFolder;
    bool exportObjectsFlag;
};

void printUsage()
{
    std::cerr << "Usage: ./testDerivates OutputFolder\n"
              << "[-e Export objects flag]\n";
    exit(1);
}

InputData readInput(int argc, char* argv[])
{
    InputData in;

    if(argc<3) printUsage();

    int opt;
    while( (opt=getopt(argc,argv,"e"))!=-1 )
    {
        switch(opt)
        {
            case 'e':
            {
                in.exportObjectsFlag = true;
                break;
            }
            default:
            {
                printUsage();
            }
        }
    }
    in.outputFolder = argv[optind];

    return in;
}

using namespace DIPaCUS;

int main(int argc, char* argv[])
{
    InputData in = readInput(argc,argv);

    std::string baseFolder = in.outputFolder + "/test/derivates";
    boost::filesystem::create_directories(baseFolder);

    std::ofstream ofs(baseFolder + "/log.txt");

    bool flag = Test::Misc::runTest(ofs,baseFolder,in.exportObjectsFlag);

    ofs.flush();
    ofs.close();

    assert(flag);

    return 0;
}