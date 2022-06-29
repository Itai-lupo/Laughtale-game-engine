#pragma once

#include <vector>
#include <string>

#include "core.h"
#include "coreCameraControler.h"
#include "material.h"

#include "colliderSystem2D.h"
#include "assetManager.h"
#include "sceneEvents.h"
#include "framebuffer.h"
#include "osEvents.h"
#include "gameobject.h"

namespace LTE
{
    class batchRenderer;
    class window;

    class scene: osEvent
    {
        private:
            framebuffer *fbo;
            batchRenderer *render;
            sceneEventsManger *eventsManger;
            gameObjectsManger *sceneHierarchy;

        public:
            scene();
            ~scene(){
                sceneCollider->close();

            }

            sceneId id;
            colliderSystem2D *sceneCollider;

            gameObject *camera;
            std::vector<gameObject*> *objects;
            
            material *backgroundColor;

            void removeById(gameObjectId id);
            
            virtual void onWindowRender(windowRenderData *sendor) override;
            
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

            void renderToTextureAtEvent(const std::string& texturePath, const std::string& eventPath);
            
            void pushObjectToRender(gameObject* obj);
            void pushPhysicsObject(gameObject* obj);
            
            void removeObjectToRender(gameObjectId objId);
            void removePhysicsObject(gameObjectId objId);

            void renderScene();

            sceneEventsManger *getEventsManger()
            {
                return eventsManger;
            }


            gameObjectId addGameObject(std::function<void(gameObjectBuilder *Builder)> buildGameObject);
            gameObject *getGameObjectByName(const std::string& name);
            gameObject *getGameObjectById(gameObjectId id);
            void removeGameObjectById(gameObjectId id);
    };

}