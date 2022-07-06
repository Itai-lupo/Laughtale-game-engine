#pragma once
#include "core.hpp"
#include "osAPI.hpp"
#include "window.hpp"

#include <string>
#include <functional>
#include <vector>
#include <glm/glm.hpp>

#include "soundDevice.hpp"

namespace LTE {

	class OSAbstractFactory
	{
		public:
            virtual ~OSAbstractFactory() = default;
			virtual windowPieceId createWindow(window *windowToCreate) = 0;
			virtual soundDevice *createInputSoundDevice() = 0;
			virtual soundDevice *createOutputSoundDevice() = 0;
			virtual osAPI *createOsApi() = 0;

			static OSAbstractFactory *init();
	};
}