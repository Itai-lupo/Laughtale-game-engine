#pragma once
#include "file.hpp"
#include "texture.hpp"

namespace LTE
{
    class jpgFile: public file
    {
        private:
        public:
            jpgFile(const std::string& filePath);

            virtual ~jpgFile();

            virtual asset *genrateAsset();
            virtual void loadFileData();

    }; 


    class jpgFileFactory: public fileFactory
    {
        public:
            jpgFileFactory(){}
    
            virtual file* createFile(const std::string& filePath)
            {
                return new jpgFile(filePath);
            }
    };
}