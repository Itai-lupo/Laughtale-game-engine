#pragma once
#include <string>
#include <functional>
#include <vector>


#include "core.h"
#include "graphicsContext.h"
#include "scene.h"
#include "renderApi.h"

#include "osEvents.h"
#include "coreInput.h"

namespace LTE 
{
	class window: osEvent
	{

		public:
			window(): osEvent({ osEventsType::WindowResize }){}
			
			std::string Title = "laughtale new window";
			unsigned int Width = 1280, Height = 720;
			bool useImGui = false;
			windowPieceId id;

			graphicsContext *context; 
			coreInput *inputManger;
			
			void onWindowResize(WindowResizeData *sendor);

			void init();
			~window();
	};
}