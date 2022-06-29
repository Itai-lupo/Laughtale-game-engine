#pragma once
#include "core.h"

namespace LTE
{
    struct sceneEventData
    {
        sceneEventData(gameObjectId id): id(id){}
        virtual ~sceneEventData() = default;

        gameObjectId id;
    };
}