#pragma once
#include <functional>
#include <vector>
#include <map>

#include "core.hpp"
#include "osEventData.hpp"
#include "mouseMoveData.hpp"
#include "KeyData.hpp"
#include "WindowResizeData.hpp"
#include "keyTypedData.hpp"
#include "mouseClickData.hpp"
#include "mouseScrollData.hpp"
#include "windowRenderData.hpp"


#include "logger.hpp"
#include "router.hpp"

namespace LTE
{
    enum osEventsType
    {
        windowRender,
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,
        WindowRender,
        WindowImGuiRender,

        keyPressed,
        keyReleased,
        keyRepeat,
        keyTyped,

        MousePressed,
        MouseReleased,
        MouseMove,
        MouseScroll,
    };

    class osEvent;
    class osEventsManger
    {
        private:
            std::map<osEventsType, std::vector<osEvent*>> eventList;
            uint32_t nextEventId;

        public:
            osEventsManger(){}

            void removeEvent(osEventsType t, eventLaughId id);
            void addEvent(osEventsType t, osEvent *callback);
            
            eventLaughId registerOsEventClass(osEvent *callback);

            template<typename eventDataType>
            void trigerEvent(eventDataType *sendor, osEventsType t);
    };

    class osEvent
    {
        private:
            eventLaughId id = 0;

        public:
            std::map<osEventsType, bool> eventsToUse;
            windowPieceId onlyRunOnWindow = 0;

            osEvent(std::vector<osEventsType> eventsToUse);

            eventLaughId getID() { return id; }

            virtual ~osEvent();

            virtual void onWindowClose(osEventData *sendor){}
            virtual void onWindowResize(WindowResizeData *sendor){}
            virtual void onWindowFocus(osEventData *sendor){}
            virtual void onWindowLostFocus(osEventData *sendor){}
            virtual void onWindowMoved(WindowResizeData *sendor){}
            virtual void onWindowRender(windowRenderData *sendor){}
            virtual void onWindowImGuiRender(windowRenderData *sendor){}
            

            virtual void onkeyPressed(KeyData *sendor){}
            virtual void onkeyReleased(KeyData *sendor){}
            virtual void onkeyRepeat(KeyData *sendor){}
            virtual void onkeyTyped(keyTypedData *sendor){}

            virtual void onMousePressed(mouseClickData *sendor){}
            virtual void onMouseReleased(mouseClickData *sendor){}
            virtual void onMouseMove(mouseMoveData *sendor){}
            virtual void onMouseScroll(mouseScrollData *sendor){}
    };

}