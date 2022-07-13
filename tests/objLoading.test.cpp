#include <gtest/gtest.h>

#include "LaughTaleEngine.hpp"
#include <imgui.h>

static inline LTE::scene *gameScene;

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

class cube: LTE::osEvent
{
    private:
        LTE::windowPieceId winId; 
        std::string name;
    public:
        LTE::gameObjectId id;
        void init(LTE::gameObjectBuilder *builder){ 
            builder->
                setObjectName(name)->
                setObjectTransform({{ 0.0f, 0.0f, 0.0f}, {1.5f, 0.0f, 0.0f}, { 1.0f, 1.0f, 1.0f}})->
                addComponent(LTE::mesh::build([=, this](LTE::mesh::meshBuilder *builder)
                    {
                        builder->setIndexBuffer(pilarIndices, 6 * 6)->
                        setVertices(pilarPostions, 8*3)->
                        setShaderName("moduleLoading/shaders/Basic.glsl");
                    }))->
                addComponent(new LTE::material(glm::vec4({1.0f, 1.0f, 0.0f, 1.0f})));
        }

        cube(LTE::windowPieceId winId, const std::string& name): LTE::osEvent({LTE::osEventsType::WindowImGuiRender, LTE::osEventsType::WindowClose}), winId(winId), name(name)
        {
            id =  gameScene->addGameObject([this](LTE::gameObjectBuilder *builder){init(builder); });
        }

        virtual void onWindowImGuiRender(LTE::windowRenderData *sendor)
        {
            ImGui::Begin(name.c_str());
            
            LTE::transform *cubeTrans =  gameScene->getGameObjectById(id)->getTransform();

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

        virtual void onWindowClose(LTE::osEventData *sendor)
        {
            LTE::app::keepRunning = false;
        }

};

TEST(moduleLoading, DISABLED_objLoad)
{
    LTE::app::init();
    
    LTE::windowPieceId winId =  LTE::app::getWindowManger()->addWindow([=](LTE::windowBuilder *build)
    {
        build->setTitle("obj file load test")->useImGui();
    });

    LTE::sceneId sceneId =  LTE::sceneManger::addScene([=](LTE::sceneBuilder *build)
    {
        build->setBackgroundColor(new LTE::material(glm::vec4({0.2f, 0.2f, 0.2f, 1.0f})));
    });

    gameScene = LTE::sceneManger::getScene(sceneId);

    cube *c1 = new cube(winId, "cube 1");
    cube *c2 = new cube(winId, "cube 2");
    
    LTE::sceneManger::getScene(sceneId)->renderToTextureAtEvent("obj file load test/screen texture", "window render/obj file load test/render scene");

    LTE::app::run();
    LTE::app::close();
    exit(0);

}
