#include <iostream>

#include <boost/filesystem.hpp>

#include "Shapes/testShapes.h"
#include "Representation/testRepresentation.h"

namespace DIPaCUS
{
    namespace Test
    {
        std::string PROJECT_FOLDER = PROJECT_DIR;
        std::string IMAGE_INPUT_PATH = PROJECT_FOLDER + "/input_images";
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
    std::cerr << "Usage: ./testBase OutputFolder\n"
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

using namespace DIPaCUS::Test;

int main(int argc, char* argv[])
{
    InputData in = readInput(argc,argv);

    std::string baseFolder = in.outputFolder + "/test/base";
    boost::filesystem::create_directories(baseFolder);

    std::ofstream ofs (baseFolder + "/log.txt");

    bool flag=true;

    flag = flag && Representation::runTest(ofs,baseFolder+"/representation",in.exportObjectsFlag);
    flag = flag && Shapes::runTest(ofs,baseFolder+"/shapes",in.exportObjectsFlag);

    assert(flag);

    ofs.flush();
    ofs.close();

    return 0;
}