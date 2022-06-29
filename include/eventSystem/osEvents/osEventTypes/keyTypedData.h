#pragma once
#include "osEventData.h"

namespace LTE
{
    struct keyTypedData: public osEventData
    {
        keyTypedData(unsigned int keycode, windowPieceId window):
            osEventData(), keycode(keycode){ windowId = window; }

        unsigned int keycode;
    };
}