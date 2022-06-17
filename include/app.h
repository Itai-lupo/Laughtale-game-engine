#pragma once
#include "core.h"
#include "OSAbstractFactory.h"
#include "osAPI.h"
#include "graphicsAPIAbstractFactory.h"

namespace LTE
{
    class app
    {
        private:
            static inline OSAbstractFactory *osFactory;
            static inline osAPI *os;
            
            static graphicsAPIAbstractFactory *openGLApiFactory;
        public:
            static void init();
            static void close();
            static void run();
            static uint64_t getTime();

            static bool keepRunning;
            static inline bool isRuning;
            static OSAbstractFactory *getOSAbstractFactory(){ return osFactory; }
            static osAPI *getOsAPI(){ return os; }
            static graphicsAPIAbstractFactory *getGraphicAPIFactory(renderAPIType type);
    };
}; 