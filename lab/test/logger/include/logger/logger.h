#ifndef DIPACUS_LOGGER_H
#define DIPACUS_LOGGER_H

#include <boost/filesystem.hpp>

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/writers/GenericWriter.h>
#include <DGtal/io/boards/Board2D.h>

namespace DIPaCUS
{

    namespace Test
    {
        class Logger
        {
        public:
            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DGtal::Z2i::Curve Curve;
            typedef DGtal::ImageContainerBySTLVector<DGtal::Z2i::Domain, unsigned char> Image2D;

            enum FormattingType{HeaderOne,HeaderTwo,Normal};

            template<class TClass>
            struct LoggableObject
            {
                LoggableObject(const TClass& object, const std::string& name):object(object),name(name){}

                const TClass& object;
                const std::string name;
            };

            Logger(std::ostream& os,const std::string& outputFolder,bool exportObjects);

            void exportObject(const Image2D& image, const std::string& name);
            void exportObject(const cv::Mat& cvImg, const std::string& name);
            void exportObject(const DigitalSet& ds, const std::string& name);
            void exportObject(const Curve& curve, const std::string& name);

            Logger& operator<(bool b);
            Logger& operator<(FormattingType fr);

            template<class TClass>
            unsigned int length(const TClass& s);

            template<class TClass>
            void headerOne(const TClass& s);

            template<class TClass>
            void headerTwo(const TClass& s);

            template<class TClass>
            void normal(const TClass& s);

            template<class TClass>
            Logger& operator<(const TClass& s);

            template<class TClass>
            Logger& operator<(const LoggableObject<TClass>& s);

            template<class TClass>
            Logger& operator-(const TClass& object);

            template<class TClass>
            Logger& operator^(const TClass& object);

            void changeOutputFolder(const std::string& newOutputFolder);

            std::string buffer();

        private:
            std::string outputFolder;
            std::ostream& os;
            bool exportObjectsFlag;

            std::stringstream ss;

            FormattingType ft;
        };


    }
}
#include "logger.hpp"

#endif //DIPACUS_LOGGER_H
