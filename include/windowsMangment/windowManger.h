#pragma once
#include <string>
#include <vector>
#include <functional>

#include "osEvents.h"
#include "core.h"
#include "window.h"
#include "windowBuilder.h"

namespace LTE
{
    class windowManger: osEvent
    {
        private:
            std::vector<window*> windows;
            windowBuilder *buildWindow;
        
        public:
            windowManger();
            ~windowManger();
            
            windowPieceId addWindow(std::function<void(windowBuilder *Builder)> buildWindow);
                    
            window *getWindow(windowPieceId windowId);
            
            void onWindowClose(osEventData *sendor);
    };
}
    