#include "../include/logger/logger.h"

namespace DIPaCUS
{
    namespace Test
    {
        Logger::Logger(std::ostream& os,const std::string& outputFolder,bool exportObjectsFlag):os(os),
        outputFolder(outputFolder),
        exportObjectsFlag(exportObjectsFlag)
        {
            boost::filesystem::create_directories(outputFolder);
        }

        void Logger::exportObject(const Image2D& image, const std::string& name)
        {
            if(exportObjectsFlag)
            {
                std::string outputPath = outputFolder + "/" + name;
                DGtal::GenericWriter<Image2D>::exportFile(outputPath,image);

                os << "Image written at: " << outputPath << "\n";
                os.flush();
            }
        }

        void Logger::exportObject(const cv::Mat& cvImg, const std::string& name)
        {
            if(exportObjectsFlag)
            {
                std::string outputPath = outputFolder + "/" + name;
                cv::imwrite(outputPath,cvImg);

                os << "CV-Image written at: " << outputPath << "\n";
                os.flush();
            }
        }

        void Logger::exportObject(const DigitalSet& ds, const std::string& name)
        {
            if(exportObjectsFlag)
            {
                std::string outputPath = outputFolder + "/" + name;

                DGtal::Board2D board;
                board << ds;

                board.saveEPS(outputPath.c_str());

                os << "DigitalSet written at: " << outputPath << "\n";
                os.flush();
            }
        }

        void Logger::exportObject(const Curve& curve, const std::string& name)
        {
            if(exportObjectsFlag)
            {
                std::string outputPath = outputFolder + "/" + name;

                DGtal::Board2D board;
                board << curve;

                board.saveEPS(outputPath.c_str());

                os << "Curve written at: " << outputPath << "\n";
                os.flush();
            }
        }

        void Logger::changeOutputFolder(const std::string& newOutputFolder)
        {
            outputFolder = newOutputFolder;
            boost::filesystem::create_directories(outputFolder);
        }

        std::string Logger::buffer()
        {
            std::string s = ss.str();

            ss.str("");
            ss.clear();

            return s;
        }

        Logger& Logger::operator<(FormattingType ft)
        {
            this->ft = ft;
        }

        Logger& Logger::operator<(bool b)
        {
            std::string s = b?"True":"False";
            os << s;

            os.flush();
            return *this;
        }
    }
}