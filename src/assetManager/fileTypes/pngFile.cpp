#include "pngFile.h"
#include "windowManger.h"

namespace LTE
{
    pngFile::pngFile(const std::string& filePath): file(filePath){}

    pngFile::~pngFile()
    {
    }

    asset *pngFile::genrateAsset()
    {
        return new texture(filePath);
    }

    void pngFile::loadFileData()
    {

    }
}