#pragma once
#include "sceneEventData.h"
#include "gameobject.h"

namespace LTE
{
    struct collisionData: public sceneEventData
    {
        collisionData(gameObjectId id, std::shared_ptr< LTE::gameObject>target): sceneEventData(id), target(target){}
        virtual ~collisionData() = default;
        std::shared_ptr< LTE::gameObject>target;
    };
}