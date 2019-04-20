#include <iostream>
#include <unistd.h>
#include <ctime>


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

    if(argc<2) printUsage();

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
    time_t now = time(0);
    ofs << ctime(&now) << "\n";

    bool flag = true;
    try
    {
        flag = flag && Test::Misc::runTest(ofs,baseFolder + "/Misc",in.exportObjectsFlag);
    }catch(const std::exception& e)
    {
        flag = false;
        ofs << e.what() << "\n";
    }

    ofs.flush();
    ofs.close();

    assert(flag);

    return 0;
}
