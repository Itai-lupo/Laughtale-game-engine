#pragma once
#include "sceneEventData.h"
#include "gameobject.h"

namespace LTE
{
    struct collisionData: public sceneEventData
    {
        collisionData(gameObjectId id, gameObject *target): sceneEventData(id), target(target){}
        virtual ~collisionData() = default;
        gameObject *target;
    };
}