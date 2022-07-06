#pragma once
#include <string>
#include <functional>
#include <vector>


#include "core.hpp"
#include "graphicsContext.hpp"
#include "scene.hpp"
#include "renderApi.hpp"

#include "osEvents.hpp"
#include "coreInput.hpp"

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