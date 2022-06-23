#pragma once
#include <string>
#include <functional>
#include <vector>


#include "core.h"
#include "graphicsContext.h"
#include "scene.h"
#include "renderApi.h"

#include "events.h"
#include "entity.h"
#include "coreInput.h"

namespace LTE 
{
	class window
	{
		private:
			static void onUpdate(gameObject *eventEntity, coreEventData *sendor);
			static void onWindowResize(gameObject *eventEntity, coreEventData *sendor);

		public:
			std::string Title = "laughtale new window";
			unsigned int Width = 1280, Height = 720;
			bool useImGui = false;
			windowPieceId id;

			graphicsContext *context; 
			coreInput *inputManger;
			


			void init();
			~window();
	};
}