#include "app.h"

#include "core.h"
#include "logger.h"
#include "windowManger.h"
#include "indexBuffer.h"
#include "soundEngine.h"
#include "soundSynthesizer.h"
#include "materialsManger.h"
#include "connectionsManager.h"
#include "filesManager.h"
#include "sceneManger.h"

#include <chrono>
#include <string>

#include "openGLAPIAbstractFactory.h"

namespace LTE
{
    graphicsAPIAbstractFactory *app::openGLApiFactory = new openGLAPIAbstractFactory();

    bool app::keepRunning = true;
    
    void app::init()
    {
        keepRunning = true;
        std::string pathToLogs =  "./logs/";
        std::string projectName =  "LTE";
        logger::init(pathToLogs, projectName);
        sceneManger::init();

        osFactory = OSAbstractFactory::init();
        os = osFactory->createOsApi();
        eventManger = new osEventsManger();
        windows = new windowManger();

        fileManager::init();
        soundEngine::init();
        materialsManger::init();
        GMNM::connectionsManager::init();
    }

    void app::close()
    {
        keepRunning = false;
        delete windows;
        delete eventManger;

        soundEngine::close();
        materialsManger::close();
        GMNM::connectionsManager::close();
        sceneManger::close();
        fileManager::close();
        logger::close();

        delete osFactory;
        delete os;
    }


    uint64_t app::getTime()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }


    graphicsAPIAbstractFactory *app::getGraphicAPIFactory(renderAPIType type)
    {
        switch (type)
        {
        case OpenGL:
                return openGLApiFactory;
            break;
        
        default:
            LAUGHTALE_ENGINR_LOG_FATAL("no render api of type: " << type);
            break;
        }
    }

    void app::run()
    {
        uint64_t startTime = getTime();
        uint64_t now = getTime();

        isRuning = true;
        while (keepRunning)
        {
            os->pollEvents();
            now = getTime();
        }   
        isRuning = false;

    }

    osEventsManger *app::getEventManger()
    {
        return eventManger;
    }

    windowManger *app::getWindowManger()
    {
        return windows;
    }

};

