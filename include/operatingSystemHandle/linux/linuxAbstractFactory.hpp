#pragma once
#include "core.hpp"
#include "OSAbstractFactory.hpp"


#include <string>
#include <functional>
#include <vector>


struct GLFWwindow;
namespace LTE {

	class linuxAbstractFactory: public OSAbstractFactory
	{
		public:
			linuxAbstractFactory();
			~linuxAbstractFactory();

			virtual osAPI *createOsApi() override;
			virtual windowPieceId createWindow(window *windowToCreate) override;

			virtual soundDevice *createInputSoundDevice() override;
			virtual soundDevice *createOutputSoundDevice() override;
	};
}