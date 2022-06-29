#include "core.h"
#include "window.h"
#include "logger.h"
#include "app.h"

#include "ImGuiEvents.h"
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <functional>

#include <GLFW/glfw3.h>


namespace LTE 
{
    void ImGuiEvents::onMousePressed(mouseClickData *sendor)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[sendor->button] = true;
    }

    void ImGuiEvents::onMouseReleased(mouseClickData *sendor)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[sendor->button] = false;
    }

    void ImGuiEvents::onMouseMove(mouseMoveData *sendor)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(sendor->xPos, sendor->yPos);
    }


    void ImGuiEvents::onMouseScroll(mouseScrollData *sendor)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += sendor->xOffset;
        io.MouseWheel += sendor->yOffset;
    }


    void ImGuiEvents::onWindowResize(WindowResizeData *sendor)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2( sendor->windowWidth, sendor->windowHeight);
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, sendor->windowWidth, sendor->windowHeight);

    }


    void ImGuiEvents::onkeyPressed(KeyData *sendor)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[sendor->key] = true;
        
        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
    }

    void ImGuiEvents::onkeyReleased(KeyData *sendor)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[sendor->key] = false;
    }

    void ImGuiEvents::onkeyTyped(keyTypedData *sendor)
    {
        ImGuiIO& io = ImGui::GetIO();
        int keycode = sendor->keycode;
        if (keycode > 0 && keycode < 0x10000)
            io.AddInputCharacter((unsigned short)keycode);
    }



    ImGuiEvents::ImGuiEvents(windowPieceId windowId): osEvent({
        osEventsType::MousePressed,
        osEventsType::MouseReleased,
        osEventsType::MouseMove,
        osEventsType::MouseScroll,
        osEventsType::WindowResize,
        osEventsType::keyPressed,
        osEventsType::keyReleased,
        osEventsType::keyTyped
    })
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)windowId, true);
        ImGui_ImplOpenGL3_Init("#version 410");

        LAUGHTALE_ENGINR_LOG_INFO("imgui init successfully");
    }

    ImGuiEvents::~ImGuiEvents()
    {
    	ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
    }

    void ImGuiEvents::onImGuiUpdate(window *data, windowRenderData *sendor)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

        app::getEventManger()->trigerEvent(sendor, osEventsType::WindowImGuiRender);    
		io.DisplaySize = ImVec2(data->Width, data->Height);
        ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}