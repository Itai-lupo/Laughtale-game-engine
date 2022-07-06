#include "componentsFactory.hpp"
#include "logger.hpp"

#include "material.hpp"
#include "squreCollider.hpp"
#include "orthographicCameraControler.hpp"
#include "envelope.hpp"

namespace LTE
{
	std::map<std::string, componentAbstractFactory*> componentsFactory::componentsTypes = 
	{
		{"material", new matrialFactory()},
		{"squreCollider", new squreColliderFactory()},
		{"orthographicCameraControler", new orthographicCameraControlerFactory()},
		{"envelope", new envelopeFactory()},
		{"squreCollider", new squreColliderFactory()},
	};

	void componentsFactory::addComponentType(const std::string& componentType, componentAbstractFactory* componentFactory)
	{
        componentsTypes[componentType] = componentFactory;

	}

	std::shared_ptr<component> componentsFactory::createComponent(const std::string& componentType)
	{
        if(componentsTypes[componentType])
            return componentsTypes[componentType]->createComponent();
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