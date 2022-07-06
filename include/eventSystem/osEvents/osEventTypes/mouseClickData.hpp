#pragma once
#include "osEventData.hpp"

namespace LTE
{
    struct mouseClickData: public osEventData
    {
        mouseClickData(int button, int mods, windowPieceId window):
            osEventData(), button(button), mods(mods){ windowId = window; }

        int button, mods;
    };
}