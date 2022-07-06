#include "sceneEvents.hpp"
#include "app.hpp"
#include "logger.hpp"
#include "sceneManger.hpp"

#include <algorithm>

namespace LTE
{ 

    sceneEvent::sceneEvent(sceneId sceneToRunOn, std::vector<sceneEventsType> eventsToUse): sceneToRunOn(sceneToRunOn)
    {
        scene *s = sceneManger::getScene(sceneToRunOn);
        id = s->getEventsManger()->registerSceneEventClass(this);
        for (sceneEventsType& eventType: eventsToUse)
        {
            s->getEventsManger()->addEvent(eventType, this);
        }
        
    }  

    sceneEvent::~sceneEvent()
    {
        scene *s = sceneManger::getScene(sceneToRunOn);

        for (auto& [eventType, usesType]: eventsToUse)
        {
            if(usesType)
                s->getEventsManger()->removeEvent(eventType, id);
        }
        
    }  

    eventLaughId sceneEventsManger::registerSceneEventClass(sceneEvent *callback)
    {
        return nextEventId++;
    }


    void sceneEventsManger::removeEvent(sceneEventsType t, eventLaughId id)
    {
        eventList[t].erase(
            std::remove_if(
                eventList[t].begin(),
                eventList[t].end(),
                [id, t](sceneEvent *e)
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

    void sceneEventsManger::addEvent(sceneEventsType t, sceneEvent *callback)
    {
        callback->eventsToUse[t] = true;
        eventList[t].push_back(callback);
    }    

#include "logger.hpp"
    template<>
    void sceneEventsManger::trigerEvent<collisionData>(collisionData *sendor, sceneEventsType t)
    {
        for(sceneEvent *callback: eventList[t])
        {
            if(callback->onlyRunOnGameObject != 0 && callback->onlyRunOnGameObject != sendor->id )
                continue;
            
            callback->onCollide(sendor);
        }
    }
}