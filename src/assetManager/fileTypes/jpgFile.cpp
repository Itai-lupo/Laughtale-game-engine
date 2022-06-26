#include "jpgFile.h"
#include "windowManger.h"

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