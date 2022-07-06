#pragma once
#include "core.hpp"
#include <string>
#include "graphicsContext.hpp"
#include "router.hpp"
#include "file.hpp"

namespace LTE
{
    
    class fileManager
    {
        private:
            static std::string filesBasePath;
            static router<file*> filesTree;

        public:
            static void setBaseFIlesPath(const std::string& filesBasePath)
            { 
                fileManager::filesBasePath = filesBasePath;
            }

            static void init();
            static void close();


            template <typename T>
            static T *getFile(const std::string& filePath)
            {
                return static_cast<T*>(getFile(filePath));
            }

            static file *getFile(const std::string& filePath);
    };
}