#pragma once
#include "component.hpp"
#include <map>
#include <string>

namespace LTE
{
	class componentsFactory
	{
		private:
			static std::map<std::string, componentAbstractFactory*> componentsTypes;
			
		public:
            static void addComponentType(const std::string& componentType, componentAbstractFactory* componentFactory);
            static std::shared_ptr<component> createComponent(const std::string& componentType);

			static void forEachComponentType(std::function<void(const std::string&)> callback);
	};
}