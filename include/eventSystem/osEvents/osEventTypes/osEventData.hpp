#pragma once
#include "core.hpp"

namespace LTE
{
    struct osEventData
    {
        osEventData(){}
        virtual ~osEventData() = default;
        windowPieceId windowId = 0;
    };
}