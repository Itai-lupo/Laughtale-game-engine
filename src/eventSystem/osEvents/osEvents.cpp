#include "osEvents.hpp"
#include "app.hpp"
#include "logger.hpp"

#include <algorithm>

namespace LTE
{ 

    osEvent::osEvent(std::vector<osEventsType> eventsToUse)
    {
        id = app::getEventManger()->registerOsEventClass(this);
        for (osEventsType& eventType: eventsToUse)
        {
            app::getEventManger()->addEvent(eventType, this);
        }
        
    }  

    osEvent::~osEvent()
    {
        
    }  

    eventLaughId osEventsManger::registerOsEventClass(osEvent *callback)
    {
        return nextEventId++;
    }


    void osEventsManger::removeEvent(osEventsType t, eventLaughId id)
    {
        eventList[t].erase(
            std::remove_if(
                eventList[t].begin(),
                eventList[t].end(),
                [id, t](osEvent *e)
                {
                    if(e->getID() == id)
                    {
                        e->eventsToUse[t] = false;
                        return true;
                    } 
                    return false; 
                }
            )
        );
    }

    void osEventsManger::addEvent(osEventsType t, osEvent *callback)
    {
        callback->eventsToUse[t] = true;
        eventList[t].push_back(callback);
    }    


    template<>
    void osEventsManger::trigerEvent(windowRenderData *sendor, osEventsType t )
    {
        if(t != osEventsType::windowRender && t != osEventsType::WindowImGuiRender)
            LAUGHTALE_ENGINR_LOG_FATAL("wrong os event type: " << t << " on event of type" << "windowRenderData")

        for(int i = 0; i < eventList[t].size(); i++)
        {
            if(eventList[t][i]->onlyRunOnWindow != 0 && eventList[t][i]->onlyRunOnWindow != sendor->windowId )
                continue;
            
            if(t == osEventsType::windowRender)
                eventList[t][i]->onWindowRender(sendor);
            if(t == osEventsType::WindowImGuiRender)
                eventList[t][i]->onWindowImGuiRender(sendor);
        }
        
    }

    template<>
    void osEventsManger::trigerEvent<osEventData>(osEventData *sendor, osEventsType t)
    {

        if(t != osEventsType::WindowClose && t != osEventsType::WindowFocus && t != osEventsType::WindowLostFocus) 
            LAUGHTALE_ENGINR_LOG_FATAL("wrong os event type: " << t << " on event of type" << "osEventData")

        for(osEvent *callback: eventList[t])
        {
            if(callback->onlyRunOnWindow != 0 && callback->onlyRunOnWindow != sendor->windowId )
                continue;
            
            if(t == osEventsType::WindowClose)
                callback->onWindowClose(sendor);
            if(t == osEventsType::WindowFocus)
                callback->onWindowFocus(sendor);
            if(t == osEventsType::WindowLostFocus)
                callback->onWindowLostFocus(sendor);
        }
    }

    template<>
    void osEventsManger::trigerEvent<mouseMoveData>(mouseMoveData *sendor, osEventsType t)
    {
        for(osEvent *callback: eventList[t])
        {
            if(callback->onlyRunOnWindow != 0 && callback->onlyRunOnWindow != sendor->windowId )
                continue;
            
            callback->onMouseMove(sendor);
        }
    }

    template<>
    void osEventsManger::trigerEvent<KeyData>(KeyData *sendor, osEventsType t)
    {
        if(t != osEventsType::keyPressed && t != osEventsType::keyReleased && t != osEventsType::keyRepeat) 
            LAUGHTALE_ENGINR_LOG_FATAL("wrong os event type: " << t << " on event of type" << "KeyData")

        for(osEvent *callback: eventList[t])
        {
            if(callback->onlyRunOnWindow != 0 && callback->onlyRunOnWindow != sendor->windowId )
                continue;
            
            if(t == osEventsType::keyPressed)
                callback->onkeyPressed(sendor);
            if(t == osEventsType::keyReleased)
                callback->onkeyReleased(sendor);
            if(t == osEventsType::keyRepeat)
                callback->onkeyRepeat(sendor);
        }
    }

    template<>
    void osEventsManger::trigerEvent<WindowResizeData>(WindowResizeData *sendor, osEventsType t)
    {
        if(t != osEventsType::WindowResize && t != osEventsType::WindowMoved)
            LAUGHTALE_ENGINR_LOG_FATAL("wrong os event type: " << t << " on event of type" << "WindowResizeData")

        for(osEvent *callback: eventList[t])
        {
            if(callback->onlyRunOnWindow != 0 && callback->onlyRunOnWindow != sendor->windowId )
                continue;
            
            if(t == osEventsType::WindowResize)
                callback->onWindowResize(sendor);
            if(t == osEventsType::WindowMoved)
                callback->onWindowMoved(sendor);
        }
    }

    template<>
    void osEventsManger::trigerEvent<keyTypedData>(keyTypedData *sendor, osEventsType t)
    {
        for(osEvent *callback: eventList[t])
        {
            if(callback->onlyRunOnWindow != 0 && callback->onlyRunOnWindow != sendor->windowId )
                continue;
            
            callback->onkeyTyped(sendor);
        }
    }

    template<>
    void osEventsManger::trigerEvent<mouseClickData>(mouseClickData *sendor, osEventsType t)
    {
        if(t != osEventsType::MousePressed && t != osEventsType::MouseReleased)
            LAUGHTALE_ENGINR_LOG_FATAL("wrong os event type: " << t << " on event of type" << "mouseClickData")

        for(osEvent *callback: eventList[t])
        {
            if(callback->onlyRunOnWindow != 0 && callback->onlyRunOnWindow != sendor->windowId )
                continue;
            
            if(t == osEventsType::MousePressed)
                callback->onMousePressed(sendor);
            if(t == osEventsType::MouseReleased)
                callback->onMouseReleased(sendor);
        }
    }

    template<>
    void osEventsManger::trigerEvent<mouseScrollData>(mouseScrollData *sendor, osEventsType t)
    {
        for(osEvent *callback: eventList[t])
        {
            if(callback->onlyRunOnWindow != 0 && callback->onlyRunOnWindow != sendor->windowId )
                continue;
            
            callback->onMouseScroll(sendor);
        }
    }
}