#include <gtest/gtest.h>

#include "LaughTaleEngine.h"
#include "imgui.h"

void WindowClose(__attribute__((unused)) LTE::gameObject *eventEntity, __attribute__((unused)) LTE::coreEventData *sendor)
{
    LTE::app::keepRunning = false;
}


float pilarPostions[8*3] = 
{
    -1 / 5.0f, -1 / 5.0f, 0 / 5.0f,
    1 / 5.0f, -1 / 5.0f, 0 / 5.0f,
    1 / 5.0f, 1 / 5.0f, 0 / 5.0f,
    -1 / 5.0f, 1 / 5.0f, 0 / 5.0f,
    -0.5f / 5.0f, -0.5f / 5.0f, 0.5f / 5.0f,
    0.5f / 5.0f, -0.5f / 5.0f, 0.5f / 5.0f,
    0.5f / 5.0f, 0.5f / 5.0f, 0.5f / 5.0f,
    -0.5f / 5.0f, 0.5f / 5.0f, 0.5f / 5.0f
};


unsigned int pilarIndices[6 * 6] = 
{
    0, 1, 3, 3, 1, 2,
    1, 5, 2, 2, 5, 6,
    5, 4, 6, 6, 4, 7,
    4, 0, 7, 7, 0, 3,
    3, 2, 7, 7, 2, 6,
    4, 5, 0, 0, 5, 1
};

void onImGui(LTE::gameObject *cube, LTE::coreEventData *sendor)
{
    ImGui::Begin(cube->getName().c_str());
    LTE::onUpdateData *eventData = static_cast<LTE::onUpdateData *>(sendor);
    
    LTE::transform *cubeTrans = cube->getTransform();

    glm::vec3 p = cubeTrans->getPostion();
    glm::vec3 r = cubeTrans->getRotation();
    glm::vec3 s = cubeTrans->getScale();

    ImGui::SliderFloat3("cube cords", (float*)&p, -2, 2);
    ImGui::SliderFloat3("cube rotation", (float*)&r, -2, 2);
    ImGui::SliderFloat3("cube scale", (float*)&s, 0, 10);

    cubeTrans->setPostion(p);
    cubeTrans->setRotation(r);
    cubeTrans->setScale(s);

    ImGui::End();

}

TEST(moduleLoading, objLoad)
{
    LTE::app::init();
    
    LTE::windowPieceId winId =  LTE::windowManger::addWindow([=](LTE::windowBuilder *build)
    {
        build->setTitle("obj file load test")->useImGui();
    });
        
    LTE::eventManger::startBuildingEvent()->
            setEventRoute("Window close/close app")->
            setEventCallback(WindowClose)->add();

    LTE::sceneId sceneId =  LTE::sceneManger::addScene([=](LTE::sceneBuilder *build)
    {
        build->setBackgroundColor(new LTE::material(glm::vec4({0.2f, 0.2f, 0.2f, 1.0f})));
    });
    
    LTE::entityTaleId cube1Id =  LTE::entityManger::addEntity([=, this](LTE::gameObject::gameObjectBuilder *builder){ 
        builder->
            setObjectName("cube 1")->
            setObjectTransform({{ 0.0f, 0.0f, 0.0f}, {1.5f, 0.0f, 0.0f}, { 1.0f, 1.0f, 1.0f}})->
            setWindowId(winId)->
            addComponent(LTE::mesh::build([=, this](LTE::mesh::meshBuilder *builder)
                {
                    builder->setIndexBuffer(pilarIndices, 6 * 6)->
                    setVertices(pilarPostions, 8*3)->
                    setShaderName("res/moduleLoading/shaders/Basic.glsl");
                }))->
            addComponent(new LTE::material(glm::vec4({1.0f, 1.0f, 0.0f, 1.0f})));
        });


    LTE::entityTaleId cube2Id =  LTE::entityManger::addEntity([=, this](LTE::gameObject::gameObjectBuilder *builder){ 
        builder->
            setObjectName("cube 2")->
            setObjectTransform({{ 0.0f, 0.0f, 0.0f}, {1.5f, 0.0f, 0.0f}, { 1.0f, 1.0f, 1.0f}})->
            setWindowId(winId)->
            addComponent(LTE::mesh::build([=, this](LTE::mesh::meshBuilder *builder)
                {
                    builder->setIndexBuffer(pilarIndices, 6 * 6)->
                    setVertices(pilarPostions, 8*3)->
                    setShaderName("res/moduleLoading/shaders/Basic.glsl");
                }))->
            addComponent(new LTE::material(glm::vec4({1.0f, 1.0f, 0.0f, 1.0f})));
        });

    LTE::sceneManger::getScene(sceneId)->objects->push_back(LTE::entityManger::getEntityById(cube1Id));
    LTE::sceneManger::getScene(sceneId)->objects->push_back(LTE::entityManger::getEntityById(cube2Id));

    LTE::eventManger::startBuildingEvent()->
        setEventRoute("ImGui render/cube1 info")->
        setEventCallback(onImGui)->
        setEntityID(cube1Id)->
        setWindowId(winId)->add();

    LTE::eventManger::startBuildingEvent()->
        setEventRoute("ImGui render/cube2 info")->
        setEventCallback(onImGui)->
        setEntityID(cube2Id)->
        setWindowId(winId)->add();

    LTE::app::run();
    LTE::app::close();
    exit(0);

}
