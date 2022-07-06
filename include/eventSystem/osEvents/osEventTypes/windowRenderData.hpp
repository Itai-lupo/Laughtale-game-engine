#pragma once
#include "osEventData.hpp"
#include "framebuffer.hpp"

namespace LTE
{
    struct windowRenderData: public osEventData
    {
        windowRenderData(framebuffer *fbo, uint64_t startTime, uint64_t currentTime, short DeltaTime):
            osEventData(), fbo(fbo), startTime(startTime), currentTime(currentTime), DeltaTime(DeltaTime){}

        framebuffer *fbo;
        uint64_t startTime, currentTime;
        short DeltaTime;
    };
}