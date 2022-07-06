#include "mp3File.hpp"

namespace LTE
{
    mp3File::mp3File(const std::string& filePath): file(filePath){}

    mp3File::~mp3File(){}
    asset *mp3File::genrateAsset()
    {
        return nullptr;
    }

    void mp3File::loadFileData()
    {

    }
}