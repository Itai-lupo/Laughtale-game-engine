#pragma once
#include "osEventData.hpp"

namespace LTE
{
    struct mouseScrollData: public osEventData
    {
        mouseScrollData(double xOffset, double yOffset, windowPieceId window):
            osEventData(), xOffset(xOffset), yOffset(yOffset){ windowId = window; }

        double xOffset, yOffset;
    };
}