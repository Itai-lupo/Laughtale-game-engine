#include "componentsFactory.hpp"
#include "logger.hpp"

#include "material.hpp"
#include "squreCollider.hpp"
#include "orthographicCameraControler.hpp"
#include "envelope.hpp"

namespace LTE
{
	std::map<std::string, std::function<std::shared_ptr<component>()>> componentsFactory::componentsTypes = 
	{
		{"material", []() -> std::shared_ptr<component>{ return std::make_shared<material>(glm::vec4{1, 1, 1, 1}); }},
		{"squreCollider", []() -> std::shared_ptr<component>{ return std::make_shared<squreCollider>(); }},
		{"orthographicCameraControler", []() -> std::shared_ptr<component>{ return std::make_shared<orthographicCameraControler>(1); }},
		{"envelope", []() -> std::shared_ptr<component>{ return std::make_shared<envelope>(); }},
		{"squreCollider", []() -> std::shared_ptr<component>{ return std::make_shared<squreCollider>(); }}
	};

	void componentsFactory::addComponentType(const std::string& componentType, std::function<std::shared_ptr<component>()> componentFactory)
	{
        componentsTypes[componentType] = componentFactory;

	}

	std::shared_ptr<component> componentsFactory::createComponent(const std::string& componentType)
	{
        if(componentsTypes[componentType])
            return componentsTypes[componentType]();
        else
        {
            LAUGHTALE_ENGINR_LOG_ERROR("component type: " << componentType << " not registry in the system. can't create component");
            return NULL;
        }
	}

	void componentsFactory::forEachComponentType(std::function<void(const std::string&)> callback)
	{
		for (auto &type : componentsTypes)
		{
			callback(type.first);
		}		
	}
}