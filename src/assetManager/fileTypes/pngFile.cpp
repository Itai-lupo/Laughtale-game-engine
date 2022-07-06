#include "pngFile.hpp"
#include "windowManger.hpp"

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