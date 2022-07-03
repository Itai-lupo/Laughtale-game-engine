
#include <vector>
#include <string>

#include "scene.h"
#include "graphicsContext.h"
#include "batchRenderer.h"
#include "window.h"

namespace LTE
{
    scene::scene(): osEvent({osEventsType::windowRender})
    {
        sceneCollider = new colliderSystem2D(id);
        backgroundColor = new material(glm::vec4({0.05f, 0.05f, 0.55f, 1.0f}));
        objects = new  std::vector<std::weak_ptr<gameObject>>;    
        
        fbo = new framebuffer(1280, 720);
        render = new batchRenderer(this);
        sceneCollider->init();
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

    void scene::pushObjectToRender(std::weak_ptr<gameObject> obj)
    {
        objects->push_back(obj);
    }

    void scene::pushPhysicsObject(std::weak_ptr<gameObject> obj)
    {
        sceneCollider->addSqureCollider(obj);
    }

    
    void scene::removeObjectToRender(gameObjectId objId)
    {
        objects->erase(std::remove_if(
            objects->begin(),
            objects->end(),
            [objId](std::weak_ptr<gameObject> obj){ return obj.lock() && obj.lock()->getId() == objId; }
        ));
    }

    void scene::removePhysicsObject(gameObjectId objId)
    {
        sceneCollider->removeSqureCollider(objId);
    }

    gameObjectId scene::addGameObject(std::function<void(gameObjectBuilder *Builder)> buildGameObject)
    {
        
        return sceneHierarchy->addGameObject(buildGameObject, id);
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