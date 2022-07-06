#include "linuxAPI.hpp"
#include <GLFW/glfw3.h>

namespace LTE 
{
	void linuxAPI::pollEvents()
	{
		glfwWaitEvents();
	}

	bool linuxAPI::isWindowOpen(windowPieceId winId)
	{
		return !glfwWindowShouldClose((GLFWwindow*)winId);
	}

	void linuxAPI::setVSyncForCurrentContext(bool enabled)
	{
		glfwSwapInterval(enabled);
	}

	void linuxAPI::makeContextCurrent(windowPieceId winId)
	{
		glfwMakeContextCurrent((GLFWwindow*)winId);
	}

	void linuxAPI::closeWindow(windowPieceId winId)
	{
		glfwDestroyWindow((GLFWwindow*)winId);
	}

	void linuxAPI::swapBuffers(windowPieceId winId)
	{
        glfwSwapBuffers((GLFWwindow*)winId);
	}

	void linuxAPI::destroyWindow(windowPieceId winId)
	{
        glfwDestroyWindow((GLFWwindow*)winId);

	}

	windowPieceId linuxAPI::getCurrentContextWindowId()
	{
		return (windowPieceId)glfwGetCurrentContext();
	}
	


	void *linuxAPI::getProcAddress()
	{
		return (void*)glfwGetProcAddress;
	}

}