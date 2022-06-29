#include "graphicsContext.h"
#include "app.h"
#include <sys/prctl.h>
#include "windowManger.h"
#include "app.h"
#include "ImGuiEvents.h"
#include "batchRenderer.h"
#include "simpleQuadRenderer.h"
#include "assetManager.h"

namespace LTE
{
    graphicsContext::graphicsContext(window *parentWin, renderAPIType type):windowId(parentWin->id), type(type)
    {
        const std::string textureToRender = parentWin->Title + "/" + "screen texture"; 
        texture *t = new texture("");
        assetManager::saveAsset(t, textureToRender);
    }
    
    void graphicsContext::Init()
    {

        contextThread = new std::thread(&graphicsContext::run, this);
    }

    graphicsContext::~graphicsContext()
    {
        windowRun = false;
        contextThread->join();
    }

    void graphicsContext::run()
    {
        std::string thradName = "con " + app::getWindowManger()->getWindow(windowId)->Title;
        prctl(PR_SET_NAME, thradName.c_str(), 0, 0, 0);

        while (!app::isRuning){}
        app::getOsAPI()->makeContextCurrent(windowId);
        
        
        api = app::getGraphicAPIFactory(type)->createRenderApi();
        api->init();
        meshFactory = app::getGraphicAPIFactory(type)->createMeshAbsrtactFactory();
		
		


        uint64_t startTime = app::getTime();
        uint64_t now = app::getTime();

        windowRenderData *sendorData = new windowRenderData(startTime, startTime, 0);

        sendorData->windowId = windowId;

        const std::string textureToRender = app::getWindowManger()->getWindow(windowId)->Title + "/" + "screen texture"; 
        
        contextRenderEngine = new simpleQuadRenderer(textureToRender);
        ImGuiEvents *ImGuiE;

        if(app::getWindowManger()->getWindow(windowId)->useImGui)
			ImGuiE = new ImGuiEvents(windowId);

        
        while (app::keepRunning && windowRun)
        {
            now = app::getTime();
            sendorData->DeltaTime = now - sendorData->currentTime;
            sendorData->currentTime = now;
            

            if(changeViewPort)
            {
                api->SetViewport(x, y, width, height);
                changeViewPort = false;
            }
            
            if(windowRun)
                app::getEventManger()->trigerEvent(sendorData, osEventsType::windowRender);
            contextRenderEngine->renderScene();

            if(windowRun && app::getWindowManger()->getWindow(windowId)->useImGui)
                ImGuiE->onImGuiUpdate(app::getWindowManger()->getWindow(windowId), sendorData);
            
            SwapBuffers();
        }   
    }

    void graphicsContext::SwapBuffers()
    {
        app::getOsAPI()->swapBuffers(windowId);
    }

    renderApi *graphicsContext::getRenderApi()
    {
        return api;
    }    

    void graphicsContext::setViewPort(int x, int y, int width, int height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        changeViewPort = true;
    }

} 