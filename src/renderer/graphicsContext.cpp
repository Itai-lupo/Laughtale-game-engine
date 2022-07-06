#include "graphicsContext.hpp"
#include "app.hpp"
#include <sys/prctl.h>
#include "windowManger.hpp"
#include "app.hpp"
#include "ImGuiEvents.hpp"
#include "batchRenderer.hpp"
#include "simpleQuadRenderer.hpp"
#include "assetManager.hpp"

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
        framebuffer *fbo = new framebuffer(app::getWindowManger()->getWindow(windowId)->Width, app::getWindowManger()->getWindow(windowId)->Height);

        windowRenderData *sendorData = new windowRenderData(fbo, startTime, startTime, 0);

        sendorData->windowId = windowId;

        const std::string textureToRender = app::getWindowManger()->getWindow(windowId)->Title + "/" + "screen texture";

        fbo->attachColorRenderTarget(assetManager::getAsset<texture>(textureToRender), 0);
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
                fbo->resize(width, height);
                changeViewPort = false;
            }
            
            if(windowRun)
                app::getEventManger()->trigerEvent(sendorData, osEventsType::windowRender);
            contextRenderEngine->renderScene(width, height);

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