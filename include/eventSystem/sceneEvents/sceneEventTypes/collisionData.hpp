#pragma once
#include "sceneEventData.hpp"
#include "gameobject.hpp"

namespace LTE
{
    struct collisionData: public sceneEventData
    {
        collisionData(gameObjectId id, std::shared_ptr< LTE::gameObject>target): sceneEventData(id), target(target){}
        virtual ~collisionData() = default;
        std::shared_ptr< LTE::gameObject>target;
    };
}