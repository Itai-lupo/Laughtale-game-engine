#pragma once
#include "core.hpp"
#include "OSAbstractFactory.hpp"
#include "osAPI.hpp"
#include "graphicsAPIAbstractFactory.hpp"
#include "osEvents.hpp"
#include "windowManger.hpp"

namespace LTE
{
    class app
    {
        private:
            static inline OSAbstractFactory *osFactory;
            static inline osAPI *os;
            static inline osEventsManger *eventManger;
            static inline windowManger *windows;

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
            static osEventsManger *getEventManger();
            static windowManger *getWindowManger();
    };
}; 