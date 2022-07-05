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
    class gameObjectsManger;
    class gameObject;

    class scene: osEvent
    {
        private:
            framebuffer *fbo;
            batchRenderer *render;
            sceneEventsManger *eventsManger;
            gameObjectsManger *sceneHierarchy;
            colliderSystem2D *sceneCollider;
            sceneId id;

        public:
            scene(sceneId id);
            ~scene(){
                delete render;
                delete fbo;
                delete eventsManger;
                delete sceneHierarchy;
                delete sceneCollider;
                delete backgroundColor;
            }

            sceneId getId(){ return id; }

            std::shared_ptr<gameObject> camera;
            material *backgroundColor;

            virtual void onWindowRender(windowRenderData *sendor) override;

            float getAspectRation()
            {
                return camera->getComponent<coreCameraControler>()->getAspectRatio();
            }

            void renderToTextureAtEvent(const std::string& texturePath, const std::string& eventPath);

            void renderScene();

            sceneEventsManger *getEventsManger()
            {
                return eventsManger;
            }


            std::shared_ptr<gameObject> addGameObject(const std::string& name);
            std::shared_ptr<gameObject> getGameObjectByName(const std::string& name);
            std::shared_ptr<gameObject> getGameObjectById(gameObjectId id);
            void removeGameObjectById(gameObjectId id);
            void forEachObject(std::function<void(std::shared_ptr<gameObject>)> callback);

            template<typename t>
            std::vector<std::shared_ptr<gameObject>> getGameObjectCacheByComponentType()
            {
                return sceneHierarchy->getGameObjectCacheByComponentType<t>();
            }
    };

}