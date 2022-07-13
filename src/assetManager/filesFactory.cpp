#include "filesFactory.hpp"
#include "logger.hpp"

#include "glslFile.hpp"
#include "jpgFile.hpp"
#include "mp3File.hpp"
#include "pngFile.hpp"

namespace LTE
{   

    std::unordered_map<std::string, fileFactory*> filesFactory::fileTypes = {
        {"mp3", new mp3FileFactory()},
        {"glsl", new glslFileFactory},
        {"png", new pngFileFactory()},
        {"jpg", new jpgFileFactory()}
    };

    void filesFactory::addFileType(const std::string& fileExt, fileFactory* fileCreater)
    {
        fileTypes[fileExt] = fileCreater;
    }

    file* filesFactory::createFile(const std::string& filePath, std::string fileType)
    {
        if(fileTypes.find(fileType) != fileTypes.end())
            return fileTypes[fileType]->createFile(filePath);
        else
        {
            LAUGHTALE_ENGINR_LOG_ERROR("file type: " << fileType << " not registry in the system. can't load file: " << filePath);
            return NULL;
        }
    }
}