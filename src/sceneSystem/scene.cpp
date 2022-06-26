
#include <vector>
#include <string>

#include "scene.h"
#include "graphicsContext.h"
#include "events.h"
#include "batchRenderer.h"
#include "window.h"

namespace LTE
{
    static scene *toRender;
    scene::scene()
    {
        sceneCollider = new colliderSystem2D();
        backgroundColor = new material(glm::vec4({0.05f, 0.05f, 0.55f, 1.0f}));
        objects = new std::vector<gameObject*>();

        eventManger::addCoustemEventsRoute("window render/obj file load test/");

        LTE::eventManger::startBuildingEvent()->
            setEventRoute("window render/obj file load test/render scene")->
            setEventCallback(renderScene)->add();
    
        
        fbo = new framebuffer(1280, 720);
        toRender = this;
    }

    void scene::renderScene(LTE::gameObject *e, LTE::coreEventData *sendor)
    {
        LTE::onUpdateData *eventData = static_cast<LTE::onUpdateData *>(sendor);
        toRender->fbo->attachColorRenderTarget(toRender->assetLibrary->getAsset<texture>(eventData->win->Title + "/" + "screen texture"), 0);
        
        if(!toRender->render)
            toRender->render = new batchRenderer(toRender, graphicsContext::getRenderApi());

        toRender->fbo->bind();
        toRender->render->renderScene();
        toRender->fbo->unbind();
    }

}