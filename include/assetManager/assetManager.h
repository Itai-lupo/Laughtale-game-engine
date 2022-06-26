#pragma once
#include "core.h"
#include <string>
#include "router.h"
#include "asset.h"

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