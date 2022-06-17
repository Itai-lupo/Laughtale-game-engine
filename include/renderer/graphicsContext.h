#pragma once
#include "renderApi.h"
#include "meshAbsrtactFactory.h"
#include "core.h"
#include "renderer.h"

#include <thread>

namespace LTE
{
    class graphicsContext
	{
        private:
            renderApi *getRenderApi();
		    windowPieceId windowId;
            renderApi *api;
            meshAbsrtactFactory *meshFactory;
            std::thread *contextThread;
            renderer *contextRenderEngine;

            bool changeViewPort = false;
            int x, y, width, height;

            void run();


        public:
            bool windowRun = true;

            void Init();
            void SwapBuffers();
	
            meshAbsrtactFactory *getMeshFactory(){ return meshFactory; }
            void setViewPort(int x, int y, int width, int height);
            
            graphicsContext(windowPieceId windowId, renderAPIType type);
            ~graphicsContext();
    };
}
