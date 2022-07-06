#include "core.hpp"
#include "window.hpp"
#include "logger.hpp"
#include "app.hpp"

#include "ImGuiEvents.hpp"
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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
        // ImGuiIO& io = ImGui::GetIO();

        // int keycode = sendor->keycode;
        // if (keycode > 0 && keycode < 0x10000)
        //     io.AddInputCharacter((unsigned short)keycode);
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
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;
        
        ImGuiStyle& style = ImGui::GetStyle();

        // float fontSize = 18.0f;// *2.0f;
		// io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", fontSize);
		// io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", fontSize);


        auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		
		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        
        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)windowId, true);
        ImGui_ImplOpenGL3_Init("#version 410");
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

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
    }
}