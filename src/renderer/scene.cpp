
#include <vector>
#include <string>

#include "scene.h"
#include "window.h"
#include "events.h"
#include "batchRenderer.h"

namespace LTE
{
    scene::scene(window *parentWindow)
    {
        sceneCollider = new colliderSystem2D();
        backgroundColor = new material(glm::vec4({0.05f, 0.05f, 0.55f, 1.0f}));
        objects = new std::vector<gameObject*>();

        eventManger::addCoustemEventsRoute("window render/" + parentWindow->Title + "/");

        LTE::eventManger::startBuildingEvent()->
            setEventRoute("window render/" + parentWindow->Title + "/")->
            setEventCallback(renderScene)->add();
    
        render = new batchRenderer(this, parentWindow->context->getRenderApi());
        
        fbo = parentWindow->context->getMeshFactory()->createFramebuffer(parentWindow->Width, parentWindow->Height);
    }

    void scene::renderScene(LTE::gameObject *e, LTE::coreEventData *sendor)
    {
        LTE::onUpdateData *eventData = static_cast<LTE::onUpdateData *>(sendor);
        scene *toRender = eventData->win->activeScene;

        toRender->fbo->attachColorRenderTarget(toRender->assetLibrary->getAsset<texture>(eventData->win->Title + "/" + "screen texture"), 0);
        

        toRender->fbo->bind();
        toRender->render->renderScene();
        toRender->fbo->unbind();
    }

}