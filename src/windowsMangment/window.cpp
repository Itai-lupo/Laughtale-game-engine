#include "window.h"
#include "ImGuiEvents.h"
#include "openGLrenderApi.h"
#include "app.h"

namespace LTE 
{
	void window::init()
	{
        context->Init();
	}

	void window::onWindowResize(WindowResizeData *sendor)
	{
		Width = sendor->windowWidth;
		Height = sendor->windowHeight;
		context->setViewPort(0, 0, sendor->windowWidth, sendor->windowHeight);
	}

	window::~window()
	{
		delete context;

		app::getOsAPI()->closeWindow(id);
	}

}