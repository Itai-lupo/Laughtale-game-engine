#pragma once
#include "core.hpp"

namespace LTE
{
    struct sceneEventData
    {
        sceneEventData(gameObjectId id): id(id){}
        virtual ~sceneEventData() = default;

        gameObjectId id;
    };
}