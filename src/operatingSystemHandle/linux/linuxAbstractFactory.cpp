#ifdef __linux__

#include "logger.hpp"
#include <GLFW/glfw3.h>

#include "OSAbstractFactory.hpp"
#include "linuxAbstractFactory.hpp"
#include "linuxAPI.hpp"
#include "window.hpp"

#include "linuxInputSoundDevice.hpp"
#include "linuxOutputSoundDevice.hpp"
#include "linuxInput.hpp"
#include "app.hpp"

#include <string>

namespace LTE 
{


	OSAbstractFactory *OSAbstractFactory::init()
	{
		return new linuxAbstractFactory();
	}

	void WindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		WindowResizeData *eventData = new WindowResizeData(width, height, (windowPieceId)window);
		app::getEventManger()->trigerEvent(eventData, osEventsType::WindowResize);
	}

	void WindowCloseCallback(GLFWwindow* window)
	{
		osEventData *eventData = new osEventData();
		eventData->windowId = (windowPieceId)window;

		app::getEventManger()->trigerEvent(eventData, osEventsType::WindowClose);
	}

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		KeyData *eventData = new KeyData(key, scancode, mods, (windowPieceId)window);
 
		osEventsType type = 
			(osEventsType)((action == GLFW_PRESS) * osEventsType::keyPressed + 
			(action == GLFW_RELEASE) * osEventsType::keyReleased +  
			(action == GLFW_REPEAT) * osEventsType::keyRepeat);

		app::getEventManger()->trigerEvent(eventData, type);
	}

	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		mouseClickData *eventData = new mouseClickData(button, mods, (windowPieceId)window);

		osEventsType type = 
			action == GLFW_PRESS? osEventsType::MousePressed : osEventsType::MouseReleased;

		app::getEventManger()->trigerEvent(eventData, type);
	}

	void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		mouseScrollData *eventData = new mouseScrollData(xOffset, yOffset, (windowPieceId)window);

		app::getEventManger()->trigerEvent(eventData, osEventsType::MouseScroll);
	}

	void CursorPosCallback(GLFWwindow* window, double xPos, double yPos)
	{
		mouseMoveData *eventData = new mouseMoveData(xPos, yPos, (windowPieceId)window);
		app::getEventManger()->trigerEvent(eventData, osEventsType::MouseMove);
	}

	void SetCharCallback(GLFWwindow* window, unsigned int keycode)
	{
		keyTypedData *eventData = new keyTypedData(keycode, (windowPieceId)window);
		app::getEventManger()->trigerEvent(eventData, osEventsType::keyTyped);
	}

	linuxAbstractFactory::linuxAbstractFactory()
	{
		
		int success = glfwInit();

		LAUGHTALE_ENGINR_CONDTION_LOG_FATAL(
			"Could not intialize GLFW!" + std::to_string(success),
				success != GLFW_TRUE);

		glfwSetErrorCallback(
			[](int error, const char* description)
			{
				LAUGHTALE_ENGINR_LOG_ERROR(
					"glfw error: \nerror code: " + 
					std::to_string(error) + 
					",\t error message" + 
					description
					);
			}
		);
	}

	
	linuxAbstractFactory::~linuxAbstractFactory()
	{
	}

	osAPI *linuxAbstractFactory::createOsApi()
	{
		return new linuxAPI();
	}

	windowPieceId linuxAbstractFactory::createWindow(window *windowToCreate)
	{
		GLFWwindow *winRef = glfwCreateWindow(windowToCreate->Width, windowToCreate->Height, windowToCreate->Title.c_str(), NULL, NULL);

		glfwSetWindowSizeCallback(winRef, WindowSizeCallback);
		glfwSetWindowCloseCallback(winRef, WindowCloseCallback);
		glfwSetKeyCallback(winRef, KeyCallback);
		glfwSetMouseButtonCallback(winRef, MouseButtonCallback);
		glfwSetScrollCallback(winRef, ScrollCallback);
		glfwSetCursorPosCallback(winRef, CursorPosCallback);
		glfwSetCharCallback(winRef, SetCharCallback);

		windowToCreate->id = (windowPieceId)winRef;
		windowToCreate->inputManger = new linuxInput(winRef);
		return windowToCreate->id;
	}

	soundDevice *linuxAbstractFactory::createInputSoundDevice()
	{
		return new linuxInputSoundDevice();
	}

	soundDevice *linuxAbstractFactory::createOutputSoundDevice()
	{
		return new linuxOutputSoundDevice();
	}

}

#endif