#pragma once
#include "file.hpp"

namespace LTE
{
    class mp3File: public file
    {
        public:
            mp3File(const std::string& filePath);

            virtual ~mp3File();
            virtual asset *genrateAsset();

            virtual void loadFileData();

    }; 


    class mp3FileFactory: public fileFactory
    {
        public:
            mp3FileFactory(){}
    
            virtual file* createFile(const std::string& filePath)
            {
                return new mp3File(filePath);
            }
    };
}