#pragma once
#include "renderApi.h"
#include "meshAbsrtactFactory.h"
#include "core.h"
#include "coreRenderer.h"

#include <thread>

namespace LTE
{
    class graphicsContext
	{
        private:
		    windowPieceId windowId;
            renderApi *api;
            meshAbsrtactFactory *meshFactory;
            std::thread *contextThread;
            coreRenderer *contextRenderEngine;

            bool changeViewPort = false;
            int x, y, width, height;

            void run();


        public:
            bool windowRun = true;

            void Init();
            void SwapBuffers();
	
            meshAbsrtactFactory *getMeshFactory(){ return meshFactory; }
            void setViewPort(int x, int y, int width, int height);
            renderApi *getRenderApi();
            
            graphicsContext(windowPieceId windowId, renderAPIType type);
            ~graphicsContext();
    };
}
