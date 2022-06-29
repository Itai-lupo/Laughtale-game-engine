#pragma once
#include <functional>
#include <vector>
#include <map>

#include "core.h"
#include "logger.h"

#include "collisionData.h"

namespace LTE
{
    enum sceneEventsType
    {
        collision
    };

    class sceneEvent;
    class sceneEventsManger
    {
        private:
            std::map<sceneEventsType, std::vector<sceneEvent*>> eventList;
            uint32_t nextEventId;

        public:
            sceneEventsManger(){}

            void removeEvent(sceneEventsType t, eventLaughId id);
            void addEvent(sceneEventsType t, sceneEvent *callback);
            
            eventLaughId registerSceneEventClass(sceneEvent *callback);

            template<typename eventDataType>
            void trigerEvent(eventDataType *sendor, sceneEventsType t);
    };

    class sceneEvent
    {
        private:
            eventLaughId id = 0;
            sceneId sceneToRunOn;

        public:
            std::map<sceneEventsType, bool> eventsToUse;
            gameObjectId onlyRunOnGameObject = 0;

            sceneEvent(sceneId sceneToRunOn, std::vector<sceneEventsType> eventsToUse);

            eventLaughId getID() { return id; }

            virtual ~sceneEvent();

            virtual void onCollide(collisionData *sendor){}
            
    };
}