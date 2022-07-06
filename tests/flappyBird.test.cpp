#include "LaughTaleEngine.hpp"

#include <gtest/gtest.h>
#include <vector>
#include <string.h>
#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <thread>
#include <chrono>
#include <algorithm>

#include <cstdlib>
#include <ctime>

#define PILAR_HOLE_WIDTH 0.15f
#define PILAR_HOLE_HIGHT 0.5f

#define PILAR_HOLE_HALF_WIDTH (PILAR_HOLE_WIDTH / 2.0f)
#define PILAR_HOLE_HALF_HIGHT (PILAR_HOLE_HIGHT / 2.0f)

#define PILAR_SPAWN_RATE 0.5f
static inline LTE::sceneId sceneId;
static inline LTE::scene *gameScene;

class pilar: public LTE::component, LTE::osEvent
{
    private:
        bool endOfScreen = false;
    public:


        pilar(): LTE::osEvent({LTE::osEventsType::windowRender})
        {
        }

        virtual void init(std::shared_ptr<LTE::gameObject> pilar) override
        {
        }

        virtual void end() 
        {
        }

        void onWindowRender(LTE::windowRenderData *sendor)
        {
            LTE::transform *pilarTransform = gameScene->getGameObjectById(getParentId())->getTransform();


            pilarTransform->changeXPostion(- 0.5f * ((float)sendor->DeltaTime) / 1000);
            if(pilarTransform->getPostion().x < -1.7f)
                endOfScreen = true;
        }        
};

class bird: public LTE::component, LTE::osEvent, LTE::sceneEvent
{
    private:
        LTE::windowPieceId debugInfoWindowId;
        
        LTE::texture *logoTex;
        LTE::texture *starTex;

        float speed  = 0.0f;
        bool failed = false;
        bool star = false;

    public:
        bird(LTE::windowPieceId debugInfoWindowId): LTE::osEvent({
            LTE::osEventsType::keyPressed,
            LTE::osEventsType::windowRender,
            LTE::osEventsType::WindowImGuiRender,
            LTE::osEventsType::WindowClose
        }), LTE::sceneEvent(sceneId, {LTE::sceneEventsType::collision}), debugInfoWindowId(debugInfoWindowId){}

        virtual void init(std::shared_ptr< LTE::gameObject> player) override
        {
            onlyRunOnGameObject = player->getId();
            
        }

        virtual void end() override
        {

        }

        void onWindowRender(LTE::windowRenderData *sendor)
        {
            speed -= ((float)sendor->DeltaTime)/1000.0f * 2;
            
            std::shared_ptr< LTE::gameObject>player = gameScene->getGameObjectById(getParentId());
            player->getTransform()->changeYPostion(((float)sendor->DeltaTime)/1000.0f * speed * !failed);
            player->getTransform()->setZRotation(glm::radians((speed - 1.5f) * 25.0f));


            if(player->getTransform()->getPostion().y < -1.0f)
                failed = true;
            if(player->getTransform()->getPostion().y > 1.0f)
                player->getTransform()->setYPostion(1.0f);  
        }
        
        void onWindowImGuiRender(LTE::windowRenderData *sendor)
        {
            ImGui::Text("player speed: %f", speed);
            ImGui::Text("player hight: %f", gameScene->getGameObjectById(getParentId())->getTransform()->getPostion().y);
            ImGui::Text("fps %.1f, %.1f", 1000.0f/(float)sendor->DeltaTime, double(ImGui::GetIO().Framerate));
            if(failed)
                ImGui::Text("GAME OVER");
        }



        virtual void onWindowClose(LTE::osEventData *sendor) override
        {
            LTE::app::keepRunning = false;
        }

        virtual void onCollide(LTE::collisionData *sendor)
        {
            failed = true;
        }

        void onkeyPressed(LTE::KeyData *sendor)
        {
            std::shared_ptr< LTE::gameObject>player = gameScene->getGameObjectById(getParentId());
            player->getComponent<LTE::envelope>()->noteOn();
            speed = 1.25f;
            player->getComponent<LTE::mesh>()->setShaderName(( player->getComponent<bird>()->star ? "res/flappyBird/bird.glsl": "res/flappyBird/Basic.glsl"));
            player->getComponent<LTE::material>()->setTexture(( player->getComponent<bird>()->star ? "res/textures/Logo.png" : "res/textures/5_star.png"));
            star = !player->getComponent<bird>()->star;
            player->getComponent<LTE::envelope>()->noteOff();
        }
};

class pilarSummener: public LTE::component, LTE::sceneEvent
{
    private:
        float pilarPostions[20] = 
        {
            -0.5,   0.5f, 0.0f,
            -0.5,  -0.5f, 0.0f,
             0.5,  -0.5f, 0.0f,
             0.5,   0.5f, 0.0f
        };


        unsigned int pilarIndices[6] = 
        {
            0, 1, 2,
            0, 3, 2,
        };
        

    public:
        pilarSummener(LTE::sceneId parentScene): LTE::sceneEvent(parentScene, {LTE::sceneEventsType::collision}){}

        virtual void init(std::shared_ptr< LTE::gameObject> summener) override
        {
            onlyRunOnGameObject = summener->getId();
            
        }

        virtual void end() override
        {

        }

        virtual void onCollide(LTE::collisionData *sendor)
        {
            
            std::srand(std::time(nullptr));
            float pilarHight = (rand() / (RAND_MAX + 1.0f) - 0.5f) * 0.7;

            LTE::gameObjectId pilarTopId = gameScene->addGameObject([&](LTE::gameObjectBuilder* builder){
                builder->
                    setObjectName("pilar top")->
                    setObjectTransform({{ 1.7f, pilarHight + 1.25f, 0.0f}, {0.0f, 0.0f, 0.0f}, { PILAR_HOLE_WIDTH, 2.0f, 1.0f}})->
                    addComponent(LTE::mesh::build([=](LTE::mesh::meshBuilder *builder)
                        {
                            builder->setIndexBuffer(pilarIndices, 6)->
                            setVertices(pilarPostions, 12)->
                            setShaderName("res/flappyBird/Basic.glsl");
                        }))->
                    addComponent(new LTE::material("res/textures/5_star.png", {1.0f, 1.0f, 0.0f, 1.0f}))->
                    addComponent(new pilar())->
                    addComponent(new LTE::squreCollider());
                });

            LTE::gameObjectId pilarBottomId = gameScene->addGameObject([=](LTE::gameObjectBuilder* builder){ 
                builder->
                    setObjectName("pilar bottom")->
                    setObjectTransform({{ 1.7f, pilarHight - 1.25f, 0.0f}, {0.0f, 0.0f, 0.0f}, { PILAR_HOLE_WIDTH, 2.0f, 1.0f}})->
                    addComponent(LTE::mesh::build([=](LTE::mesh::meshBuilder *builder)
                        {
                            builder->setIndexBuffer(pilarIndices, 6)->
                            setVertices(pilarPostions, 12)->
                            setShaderName("res/flappyBird/Basic.glsl");
                        }))->
                    addComponent(new LTE::material("res/textures/5_star.png", {1.0f, 1.0f, 0.0f, 1.0f}))->
                    addComponent(new pilar())->
                    addComponent(new LTE::squreCollider());
                });
        }
};

class pilarDestroyer: public LTE::component, LTE::sceneEvent
{
    private:
        
    public:
        pilarDestroyer(LTE::sceneId parentScene): LTE::sceneEvent(parentScene, {LTE::sceneEventsType::collision}){}

        virtual void init(std::shared_ptr< LTE::gameObject> destroyer) override
        {
            onlyRunOnGameObject = destroyer->getId();
        }

        virtual void end() override
        {
        }

        virtual void onCollide(LTE::collisionData *sendor)
        {
            try{
                gameScene->getGameObjectById(sendor->id)->getComponent<LTE::envelope>()->noteOn();
                gameScene->getGameObjectById(sendor->id)->getComponent<LTE::envelope>()->noteOff();

                gameScene->removeGameObjectById(sendor->target->getId());
            }
            catch(LTE::GameObjectNotFoundException * e)
            {

            }
        }
};



class flappyBird : public ::testing::Test
{
    private:
        LTE::windowPieceId gameWindowId;
        LTE::windowPieceId debugInfoWindowId;



        void initWindows()
        {
            gameWindowId =  LTE::app::getWindowManger()->addWindow([=](LTE::windowBuilder *build)
            {
                build->setTitle("flappyBird");
            });
            
            // debugInfoWindowId = LTE::app::getWindowManger()->addWindow([=](LTE::windowBuilder *build)
            // {
            //     build->setHeight(600)->setWidth(600)->setTitle("debug Info Window")->useImGui();
            // });
        }

    private:
        float birdPostions[6 * 3] = 
        {
             0.0f,    0.5f ,  0.0f, //  0.5f,   1.0f ,
             0.5f,    0.25f,  0.0f, //  1.0f,   0.75f,
             0.5f,   -0.25f,  0.0f, //  1.0f,   0.25f,
             0.0f,   -0.5f ,  0.0f, //  0.5f,   0.0f ,
            -0.5f,   -0.25f,  0.0f, //  0.0f,   0.25f,
            -0.5f,   0.25f,   0.0f //  0.0f,   0.75f,
        };


        unsigned int birdIndices[12] = 
        {
            0, 1, 5,
            1, 2, 4,
            2, 3, 4,
            1, 4, 5,
        };

        float pilarPostions[12] = 
        {
            -0.5,  0.5f, 0.0f,
            -0.5, -0.5f, 0.0f,
             0.5, -0.5f, 0.0f, 
             0.5,  0.5f, 0.0f  
        };


        unsigned int pilarIndices[6] = 
        {
            0, 1, 2,
            0, 3, 2,
        };
        

    public:        
        void SetUp()
        { 
            LTE::app::init();
            initWindows();

            sceneId =  LTE::sceneManger::addScene([=](LTE::sceneBuilder *build)
            {
                build->setBackgroundColor(new LTE::material(glm::vec4({0.2f, 0.2f, 0.2f, 1.0f})));
            });
 
            gameScene = LTE::sceneManger::getScene(sceneId);

            LTE::gameObjectId playerId =  gameScene->addGameObject([=, this](LTE::gameObjectBuilder*builder){ 
                builder->
                    setObjectName("player")->
                    setObjectTransform({{ -0.9, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, { 0.2, 0.2f, 0.0f}})->
                    addComponent(LTE::mesh::build([=, this](LTE::mesh::meshBuilder *builder)
                        {
                            builder->setIndexBuffer(birdIndices, 12)->
                            setVertices(birdPostions, 6 * 3)->
                            setShaderName("res/flappyBird/bird.glsl");
                        }))->
                    addComponent((new LTE::envelope())
                        ->setFrequency(440.0f)->
                        setSondWaveType(LTE::analogSqure)->
                        setAttackTime(0.001)->
                        setDecayTime(0.5)->
                        setReleaseTime(0.1)->
                        setStartAmplitude(1.0)->
                        setSustainAmplitude(0.0f))->
                    addComponent(new LTE::material("res/textures/Logo.png", glm::vec4({0.0f, 0.0f, 0.0f, 1.0f})))->
                    addComponent(new LTE::squreCollider())->
                    addComponent(new bird(debugInfoWindowId));
                });


            std::srand(std::time(nullptr));
            float pilarHight = (rand() / (RAND_MAX + 1.0f) - 0.5f) * 0.7;

            LTE::gameObjectId pilarTopId = gameScene->addGameObject([=, this](LTE::gameObjectBuilder*builder){ 
                builder->
                    setObjectName("pilar top")->
                    setObjectTransform({{ 1.7f, pilarHight + 1.25f, 0.0f}, {0.0f, 0.0f, 0.0f}, { PILAR_HOLE_WIDTH, 2.0f, 1.0f}})->
                    addComponent(LTE::mesh::build([=, this](LTE::mesh::meshBuilder *builder)
                        {
                            builder->setIndexBuffer(pilarIndices, 6)->
                            setVertices(pilarPostions, 12)->
                            setShaderName("res/flappyBird/Basic.glsl");
                        }))->
                    addComponent(new LTE::material("res/textures/5_star.png", {1.0f, 1.0f, 0.0f, 1.0f}))->
                    addComponent(new pilar())->
                    addComponent(new LTE::squreCollider());
                });

            LTE::gameObjectId pilarBottomId = gameScene->addGameObject([=, this](LTE::gameObjectBuilder*builder){ 
                builder->
                    setObjectName("pilar bottom")->
                    setObjectTransform({{ 1.7f, pilarHight - 1.25f, 0.0f}, {0.0f, 0.0f, 0.0f}, { PILAR_HOLE_WIDTH, 2.0f, 1.0f}})->
                    addComponent(LTE::mesh::build([=, this](LTE::mesh::meshBuilder *builder)
                        {
                            builder->setIndexBuffer(pilarIndices, 6)->
                            setVertices(pilarPostions, 12)->
                            setShaderName("res/flappyBird/Basic.glsl");
                        }))->
                    addComponent(new LTE::material("res/textures/5_star.png", {1.0f, 1.0f, 0.0f, 1.0f}))->
                    addComponent(new pilar())->
                    addComponent(new LTE::squreCollider());
                });

            LTE::gameObjectId pilarSummenerId =  gameScene->addGameObject([=, this](LTE::gameObjectBuilder*builder){ 
                builder->
                    setObjectName("pilar summener")->
                    setObjectTransform({{ 0.8f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}, { 0.1f, 0.1f, 1.0f}})->
                    addComponent(new LTE::squreCollider())->
                    addComponent(new pilarSummener(sceneId));
                });

            LTE::gameObjectId pilarDestroyerId =  gameScene->addGameObject([=, this](LTE::gameObjectBuilder*builder){ 
                builder->
                    setObjectName("pilar destroyer")->
                    addComponent((new LTE::envelope())
                        ->setFrequency(500.0f)->
                        setSondWaveType(LTE::sin)->
                        setAttackTime(0.001)->
                        setDecayTime(0.3)->
                        setReleaseTime(0.1)->
                        setStartAmplitude(1.0)->
                        setSustainAmplitude(0.0f))->
                    setObjectTransform({{ -1.7f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, { 0.1f, 2.0f, 1.0f}})->
                    addComponent(new LTE::squreCollider())->
                    addComponent(new pilarDestroyer(sceneId));
                });


    
            LTE::sceneManger::getScene(sceneId)->renderToTextureAtEvent("flappyBird/screen texture", "window render/flappyBird/render scene");
  
        }

        void TearDown() 
        { 
            LTE::app::close();
        }
};



TEST_F(flappyBird,  DISABLED_testGames)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    LTE::app::run();
}
