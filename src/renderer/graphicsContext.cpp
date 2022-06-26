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
    graphicsContext::graphicsContext(windowPieceId windowId, renderAPIType type):windowId(windowId), type(type)
    {
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
        std::string thradName = "con " + windowManger::getWindow(windowId)->Title;
        prctl(PR_SET_NAME, thradName.c_str(), 0, 0, 0);

        app::getOsAPI()->makeContextCurrent(windowId);
        
        
        api = app::getGraphicAPIFactory(type)->createRenderApi();
        api->init();
        meshFactory = app::getGraphicAPIFactory(type)->createMeshAbsrtactFactory();
		
		


        uint64_t startTime = app::getTime();
        uint64_t now = app::getTime();

        onUpdateData *sendorData = new onUpdateData(startTime, startTime, 0);

        sendorData->win = windowManger::getWindow(windowId);
        sendorData->windowId = windowId;
        sendorData->route = "window render/" + sendorData->win->Title + "/";

        const std::string textureToRender = sendorData->win->Title + "/" + "screen texture"; 
        
        assetManager::saveAsset(new texture(""), textureToRender);
        eventManger::addCoustemEventsRoute("window render/" + sendorData->win->Title + "/");
        
        contextRenderEngine = new simpleQuadRenderer(textureToRender, getRenderApi());
        
        if(sendorData->win->useImGui)
			initImGui(windowId);

        while (!app::isRuning){}
        
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
            
            eventManger:: trigerEvent(sendorData);
            contextRenderEngine->renderScene();

            if(sendorData->win->useImGui)
                onImGuiUpdate(sendorData->win, sendorData);
            
            SwapBuffers();



    		// sendorData->win->activeScene->sceneCollider->checkCollision();


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