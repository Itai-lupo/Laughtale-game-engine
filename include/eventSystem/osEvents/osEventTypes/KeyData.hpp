#pragma once
#include "osEventData.hpp"

namespace LTE
{
    struct KeyData: public osEventData
    {
        KeyData(int key, int scancode, int mods, windowPieceId window):
            osEventData(), key(key), scancode(scancode), mods(mods){ windowId = window;}

        int key, scancode, mods;
    };
}