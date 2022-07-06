#pragma once
#include "file.hpp"
#include "texture.hpp"

namespace LTE
{
    class pngFile: public file
    {
        public:
            pngFile(const std::string& filePath);

            virtual ~pngFile();

            virtual asset *genrateAsset();
            virtual void loadFileData();

    }; 


    class pngFileFactory: public fileFactory
    {
        public:
            pngFileFactory(){}
    
            virtual file* createFile(const std::string& filePath)
            {
                return new pngFile(filePath);
            }
    };
}