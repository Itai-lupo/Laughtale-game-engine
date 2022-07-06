#pragma once
#include "file.hpp"
#include <string>
#include <unordered_map>

namespace LTE
{
    class filesFactory
    {
        private:
            static std::unordered_map<std::string, fileFactory*> fileTypes;

        public:
            static void addFileType(const std::string& fileExt, fileFactory* fileCreater);
            static file* createFile(const std::string& filePath, std::string fileType);
    };
}