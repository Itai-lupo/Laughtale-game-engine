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

            std::shared_ptr<LTE::gameObject> camera;
            std::vector<std::weak_ptr<gameObject>> *objects;
            
            material *backgroundColor;

            void removeById(gameObjectId id);
            
            virtual void onWindowRender(windowRenderData *sendor) override;
            
            

            float getAspectRation()
            {
                return camera->getComponent<coreCameraControler>()->getAspectRatio();
            }

            void renderToTextureAtEvent(const std::string& texturePath, const std::string& eventPath);
            
            void pushObjectToRender(std::weak_ptr<gameObject> obj);
            void pushPhysicsObject(std::weak_ptr<gameObject> obj);
            
            void removeObjectToRender(gameObjectId objId);
            void removePhysicsObject(gameObjectId objId);

            void renderScene();

            sceneEventsManger *getEventsManger()
            {
                return eventsManger;
            }


            gameObjectId addGameObject(std::function<void(gameObjectBuilder *Builder)> buildGameObject);
            std::shared_ptr< LTE::gameObject>getGameObjectByName(const std::string& name);
            std::shared_ptr< LTE::gameObject>getGameObjectById(gameObjectId id);
            void removeGameObjectById(gameObjectId id);
    };

}