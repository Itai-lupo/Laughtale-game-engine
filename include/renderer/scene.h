#pragma once

#include <vector>
#include <string>

#include "core.h"
#include "coreCameraControler.h"
#include "material.h"

#include "colliderSystem2D.h"
#include "assetManager.h"


namespace LTE
{
    class scene
    {
        public:
            scene()
            {
                sceneCollider = new colliderSystem2D();
                backgroundColor = new material(glm::vec4({0.05f, 0.05f, 0.05f, 1.0f}));
                objects = new std::vector<gameObject*>();
            }

            ~scene(){}
            
            colliderSystem2D *sceneCollider;

			assetManager *assetLibrary;

            gameObject *camera;
            std::vector<gameObject*> *objects;
            
            material *backgroundColor;

            void removeById(entityTaleId id);
            
            std::vector<gameObject*> getObjectsByName(const std::string& objectName)
            {
                std::vector<gameObject*> objectWithName;
                for(gameObject *obj: *objects)
                {
                    if(obj->getName() == objectName)
                        objectWithName.push_back((obj));
                }
                return objectWithName;
            }

            template<typename objectType> std::vector<objectType> getObjectsByName(const std::string& objectName)
            {
                std::vector<objectType> objectWithName;
                for(gameObject *obj: *objects)
                {
                    if(obj->getName() == objectName && static_cast<objectType>(obj))
                        objectWithName.push_back(static_cast<objectType>(obj));
                }
                return objectWithName;
            }

            float getAspectRation()
            {
                return camera->getComponent<coreCameraControler>()->getAspectRatio();
            }
    };

}