#pragma once
#include "core.hpp"
#include <string>
#include "router.hpp"
#include "asset.hpp"

namespace LTE
{
    
    class assetManager
    {
        private:
            static inline router<asset*> assetsTree;

        public:

            static void saveAsset(asset *toSave, const std::string& filePath);
            static void loadAssetFromFile(const std::string& filePath);

            template <typename T>
            static T *getAsset(const std::string& filePath)
            {
                return static_cast<T*>(getAsset(filePath));
            }

            static asset *getAsset(const std::string& filePath);

    };
}