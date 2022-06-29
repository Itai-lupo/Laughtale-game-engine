#pragma once
#include "osEventData.h"

namespace LTE
{
    struct WindowResizeData: public osEventData
    {
        WindowResizeData(int width, int height, windowPieceId window):
            osEventData(), windowWidth(width), windowHeight(height){ windowId = window; }

        int windowWidth, windowHeight;
    };
}