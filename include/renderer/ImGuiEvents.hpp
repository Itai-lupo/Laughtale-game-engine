#pragma once
#include "osEvents.hpp"

struct GLFWwindow;
namespace LTE 
{
    class ImGuiEvents: osEvent
    {
        public:
            void onMousePressed(mouseClickData *sendor);
            void onMouseReleased(mouseClickData *sendor);
            void onMouseMove(mouseMoveData *sendor);

            void onMouseScroll(mouseScrollData *sendor);

            void onWindowResize(WindowResizeData *sendor);

            void onkeyPressed(KeyData *sendor);
            void onkeyReleased(KeyData *sendor);
            void onkeyTyped(keyTypedData *sendor);

            ImGuiEvents(windowPieceId windowId);
            ~ImGuiEvents();

            void onImGuiUpdate(window *data, windowRenderData *eventData);
    };
}