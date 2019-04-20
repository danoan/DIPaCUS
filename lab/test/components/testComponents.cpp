#include <unistd.h>

#include "data.h"
#include "testNeighborhood.h"
#include "testProperties.h"
#include "testSetOperations.h"
#include "testTransform.h"
#include "testMorphology.h"

struct OutputFolders
{
    std::string morphology;
    std::string neighborhood;
    std::string properties;
    std::string setOperations;
    std::string transform;
};

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

InputData readInput(int argc, char* argv[])
{
    InputData in;

    if(argc<2)
    {
        std::cerr << "Output folder expected!\n";
        exit(1);
    }

    int opt;
    while( (opt=getopt(argc,argv,"e") )!=-1 )
    {
        switch(opt)
        {
            case 'e':
            {
                in.exportObjectsFlag=true;
                break;
            }
            default:
            {
                std::cerr << "Usage: ./testComponents OutputFolder "
                          << "[-e Export Objects]\n";
                exit(1);
            }
        }
    }

    in.outputFolder = argv[optind];

    return in;
}

OutputFolders createDirectories(const std::string& baseFolder)
{
    OutputFolders OF;
    OF.morphology = baseFolder + "/morphology";
    OF.neighborhood = baseFolder + "/neighborhood";
    OF.properties = baseFolder + "/properties";
    OF.setOperations = baseFolder + "/setOperations";
    OF.transform = baseFolder + "/transform";

    return OF;
}

using namespace DIPaCUS;

int main(int argc, char* argv[])
{
    InputData in = readInput(argc,argv);

    std::string baseFolder = in.outputFolder;
    baseFolder += "/test/components";
    boost::filesystem::create_directories(baseFolder);

    OutputFolders OF = createDirectories(baseFolder);

    std::ofstream ofs(baseFolder+"/log.txt");

    bool flag = true;
    flag = flag && Test::Morphology::runTest(ofs,OF.morphology,in.exportObjectsFlag);
    flag = flag && Test::Neighborhood::runTest(ofs,OF.neighborhood,in.exportObjectsFlag);
    flag = flag && Test::Properties::runTest(ofs,OF.properties,in.exportObjectsFlag);
    flag = flag && Test::SetOperations::runTest(ofs,OF.setOperations,in.exportObjectsFlag);
    flag = flag && Test::Transform::runTest(ofs,OF.transform,in.exportObjectsFlag);

    ofs.flush();
    ofs.close();

    assert(flag);

    return 0;
}
