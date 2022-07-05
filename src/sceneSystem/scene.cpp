
#include <vector>
#include <string>

#include "scene.h"
#include "graphicsContext.h"
#include "batchRenderer.h"
#include "window.h"
#include "gameobject.h"

namespace LTE
{
    scene::scene(sceneId id): osEvent({osEventsType::windowRender}), id(id)
    {
        sceneCollider = new colliderSystem2D(this);
        backgroundColor = new material(glm::vec4({0.05f, 0.05f, 0.55f, 1.0f}));
        
        fbo = new framebuffer(1280, 720);
        render = new batchRenderer(this);
        eventsManger = new sceneEventsManger();
        sceneHierarchy = new gameObjectsManger();
    }

    void scene::renderToTextureAtEvent(const std::string& texturePath, const std::string& eventPath)
    {
        fbo->attachColorRenderTarget(assetManager::getAsset<texture>(texturePath), 0);
    }

    void scene::onWindowRender(windowRenderData *sendor)
    {
        onlyRunOnWindow = sendor->windowId;
        fbo->bind();
        render->renderScene();
        fbo->unbind();
    }

    std::shared_ptr<gameObject> scene::addGameObject(const std::string& name)
    {
        return sceneHierarchy->addGameObject(name);
    }

    std::shared_ptr< LTE::gameObject>scene::getGameObjectByName(const std::string& name)
    {
        return sceneHierarchy->getGameObjectByName(name);
    }

    std::shared_ptr< LTE::gameObject>scene::getGameObjectById(gameObjectId id)
    {
        return sceneHierarchy->getGameObjectById(id);
    }

    void scene::removeGameObjectById(gameObjectId id)
    {
        sceneHierarchy->removeGameObjectById(id);
    }

    void scene::forEachObject(std::function<void(std::shared_ptr<gameObject>)> callback)
    {
        sceneHierarchy->forEachObject(callback);
    }
}