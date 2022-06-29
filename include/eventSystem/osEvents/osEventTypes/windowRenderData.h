#pragma once
#include "osEventData.h"

namespace LTE
{
    struct windowRenderData: public osEventData
    {
        windowRenderData(uint64_t startTime, uint64_t currentTime, short DeltaTime):
            osEventData(), startTime(startTime), currentTime(currentTime), DeltaTime(DeltaTime){}

        uint64_t startTime, currentTime;
        short DeltaTime;
    };
}