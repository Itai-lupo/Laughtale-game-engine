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
            static inline thread_local meshAbsrtactFactory *meshFactory = NULL;
            static inline thread_local renderApi *api;
		    
            renderAPIType type;
            windowPieceId windowId;
            std::thread *contextThread;
            coreRenderer *contextRenderEngine;

            bool changeViewPort = false;
            int x, y, width, height;

            void run();


        public:
            bool windowRun = true;

            void Init();
            void SwapBuffers();
	
            void setViewPort(int x, int y, int width, int height);
            static renderApi *getRenderApi();
            
            graphicsContext(windowPieceId windowId, renderAPIType type);
            ~graphicsContext();

            static meshAbsrtactFactory* getMeshFactory(){ return meshFactory; }
    };
}
