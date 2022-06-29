#pragma once
#include "osEventData.h"

namespace LTE
{
    struct mouseMoveData: public osEventData
    {
        mouseMoveData(double xPos, double yPos, windowPieceId window):
            osEventData(), xPos(xPos), yPos(yPos){ windowId = window; }

        double xPos, yPos;
    };
}