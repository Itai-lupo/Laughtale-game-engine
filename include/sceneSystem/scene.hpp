#pragma once

#include <vector>
#include <string>

#include "core.hpp"
#include "coreCameraControler.hpp"
#include "material.hpp"

#include "colliderSystem2D.hpp"
#include "assetManager.hpp"
#include "sceneEvents.hpp"
#include "framebuffer.hpp"
#include "osEvents.hpp"
#include "gameobject.hpp"

namespace LTE
{
    class batchRenderer;
    class window;
    class gameObjectsManger;
    class gameObject;

    class scene: osEvent
    {
        private:
            batchRenderer *render;
            sceneEventsManger *eventsManger;
            gameObjectsManger *sceneHierarchy;
            colliderSystem2D *sceneCollider;
            sceneId id;

        public:
            scene(sceneId id);
            ~scene(){
                delete render;
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