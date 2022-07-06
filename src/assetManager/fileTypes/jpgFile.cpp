#include "jpgFile.hpp"
#include "windowManger.hpp"

namespace LTE
{
    jpgFile::jpgFile(const std::string& filePath): file(filePath){}

    jpgFile::~jpgFile()
    {
    }

    asset *jpgFile::genrateAsset()
    {
        return new texture(filePath);
    }

    void jpgFile::loadFileData()
    {

    }
}