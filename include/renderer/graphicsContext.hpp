#pragma once
#include "renderApi.hpp"
#include "meshAbsrtactFactory.hpp"
#include "core.hpp"
#include "coreRenderer.hpp"

#include <thread>

namespace LTE
{
    class window;
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
            
            graphicsContext(window *parentWin, renderAPIType type);
            ~graphicsContext();

            static meshAbsrtactFactory* getMeshFactory(){ return meshFactory; }
    };
}
