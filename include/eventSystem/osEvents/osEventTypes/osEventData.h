#pragma once
#include "core.h"

namespace LTE
{
    struct osEventData
    {
        osEventData(){}
        virtual ~osEventData() = default;
        windowPieceId windowId = 0;
    };
}