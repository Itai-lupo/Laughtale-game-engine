#include "window.h"
#include "ImGuiEvents.h"
#include "openGLrenderApi.h"
#include "app.h"

namespace LTE 
{
	void window::init(){

		eventManger::addCoustemEventsRoute("Window resize/handel window resize/");
		
		eventManger::startBuildingEvent()->
				setEventRoute("Window resize/handel window resize/" + Title)->
				setEventCallback(onWindowResize)->
				setWindowId(id)->add();

        context->Init();
		
	}

	void window::onWindowResize(gameObject *eventEntity, coreEventData *sendor)
	{
		WindowResizeData* sendorData = dynamic_cast<WindowResizeData*>(sendor);

		sendorData->win->Width = sendorData->windowWidth;
		sendorData->win->Height = sendorData->windowHeight;
		sendorData->win->context->setViewPort(0, 0, sendorData->windowWidth, sendorData->windowHeight);
	}

	window::~window()
	{
		delete context;

		app::getOsAPI()->closeWindow(id);
		
		eventManger::removeEvent("Window resize/handel window resize/" + Title);
		eventManger::removeEvent("App update/winow render/" + Title);
	}

}