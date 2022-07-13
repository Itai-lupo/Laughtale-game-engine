#include <filesystem>
#include <dlfcn.h>
#include <stdlib.h>

#include "filesManager.hpp"
#include "filesFactory.hpp"

#include "component.hpp"
#include <memory>

namespace LTE
{
    file *createFile(const std::string& fileType){ return NULL; }
    
    std::string fileManager::filesBasePath = "./assets/";
    router<file*> fileManager::filesTree;

    // todo: refactor into a file type, add preprocesor and add more contorle over what to load and the compiler argumant as well as stream the compiler output into ui debug console.
    void compileAndLoadFileTemp()
    {
        system("clang -shared assets/src/testComponent.cpp -I include/utls -I include/eventSystem -I include/defines -lstdc++  -fdeclspec -fPIC -Wl,-undefined,error -Wl,-flat_namespace -fvisibility=hidden -o test.so");
        
        void *fLib = dlopen("./test.so", RTLD_LAZY);
        if ( !fLib ) {
            LAUGHTALE_ENGINR_LOG_ERROR("Cannot open library: " << dlerror());
        }
        

        if ( fLib ) {
            std::shared_ptr<component> ( *fn )() = (std::shared_ptr<component> ( * )()) dlsym(fLib, "createComponent");

            if(fn)
            {
                std::shared_ptr<component> a = fn();
                LAUGHTALE_ENGINR_LOG_INFO("A")
                if(a)
                    LAUGHTALE_ENGINR_LOG_INFO(a->getName())
                else
                    LAUGHTALE_ENGINR_LOG_INFO("E" << a)
            }
            else
                LAUGHTALE_ENGINR_LOG_ERROR("Cannot get symbol from library: " << dlerror());

            dlclose ( fLib );
        }
    }
    
    void fileManager::init()
    {
        for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(filesBasePath))
        {
            if (!dirEntry.is_directory() && std::string(dirEntry.path().extension()) != "")
            {
                filesTree.addRoute(std::string(dirEntry.path().relative_path()).erase(0, 2).append("/"));

                std::string fileType = std::string(dirEntry.path().extension()).erase(0, 1);
                std::string filePath = std::string(dirEntry.path()).erase(0, 2);

                file *fileInDirEntry = filesFactory::createFile(filePath, fileType);
                if(fileInDirEntry)
                {
                    fileInDirEntry->loadFileData();
                    filesTree.addValue(filePath, fileInDirEntry);
                }
            }
        }

        
    }

    void fileManager::close()
    {
        filesTree.clearAndDelete();
    }

    file *fileManager::getFile(const std::string& filePath)
    {
        return filesTree["assets/" + filePath];
    }
}