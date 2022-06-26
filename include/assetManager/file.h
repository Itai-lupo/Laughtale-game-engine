#pragma once
#include "core.h"
#include "asset.h"
#include <string>

namespace LTE
{
    class file
    {
        protected:
            std::string filePath;
        public:
            virtual ~file() = default;
            file(const std::string& filePath): filePath(filePath){}

            virtual asset *genrateAsset() = 0;
            virtual void loadFileData() = 0;

            std::string getFilePath(){ return filePath; }
    }; 

    class fileFactory
    {
        public:
            virtual ~fileFactory() = default;
            virtual file* createFile(const std::string& filePath) = 0;
    };
}