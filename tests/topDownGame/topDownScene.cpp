#include "LaughTaleEngine.h"
#include "openGLTexture.h"


#include <gtest/gtest.h>
#include <vector>
#include <string.h>
#include "imgui.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <thread>
#include <chrono>
#include <algorithm>

#include <cstdlib>
#include <ctime>

static inline LTE::sceneId sceneId;
static inline LTE::scene *gameScene;
class player: public LTE::component, LTE::osEvent
{
    private:
        static inline int updateCounter = 0;
        static inline int animationCounter = 0;
        static inline const float playerSpeed = 0.6f;
    public:
    
        player(): LTE::osEvent({LTE::osEventsType::windowRender, LTE::osEventsType::WindowClose}){

        }

        virtual void init(LTE::gameObject *parent)
        {

        }

        virtual void end()
        {

        }

        void onWindowClose(LTE::osEventData *sendor)
        {
            LTE::app::keepRunning = false;
        }        

        void onWindowRender(LTE::windowRenderData *sendor)
        {
            LTE::material *playerMatreial = gameScene->getGameObjectById(getParentId())->getComponent<LTE::material>();
            LTE::transform *playerPostion = gameScene->getGameObjectById(getParentId())->getTransform();

            LTE::window *win = LTE::app::getWindowManger()->getWindow(sendor->windowId);
            bool goLeft = win->inputManger->isKeyPressed(LT_KEY_LEFT);
            bool goRight = win->inputManger->isKeyPressed(LT_KEY_RIGHT);
            bool goUp = win->inputManger->isKeyPressed(LT_KEY_UP);
            bool goDown = win->inputManger->isKeyPressed(LT_KEY_DOWN);
            
            playerMatreial->setTileIndex(1, 3);

            glm::vec2 delta = { 
                (goRight - goLeft),
                (goUp - goDown),
               };

            if((delta == glm::vec2({0, 0})))
                return;
                

            delta = glm::normalize(delta) * (playerSpeed * sendor->DeltaTime / 1000.0f);

            playerPostion->changeXPostion(delta.x);
            playerPostion->changeYPostion(delta.y);
            
            if(goRight)
                playerMatreial->setTileIndex(animationCounter, 1);
            
            
            if(goLeft)
                playerMatreial->setTileIndex(animationCounter, 2);
            
            if(goUp)
                playerMatreial->setTileIndex(animationCounter, 0);
                     
            if(goDown)
                playerMatreial->setTileIndex(animationCounter, 3); 
            
            if(updateCounter++ % 8 == 0)
                animationCounter += animationCounter++ % 4;
        }
};



class topDownGame : public ::testing::Test
{
    private:


        LTE::windowPieceId gameWindowId;

        void initWindows()
        {

            gameWindowId =  LTE::app::getWindowManger()->addWindow([=](LTE::windowBuilder *build)
            {
                build->setHeight(1000)->setWidth(1000)->setTitle("rpg");
            });
        }

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


            LTE::assetManager::getAsset<LTE::texture>("res/topDownScene/textures/Meta data assets files/ENVIRONMENT/tilesets/dungeon-tileset.png")->
                setSprtieData(
                    {
                        {{1, 48}, {15, 15}},
                        {{1, 66}, {16, 14}},
                    
                    });
            
            LTE::assetManager::getAsset<LTE::texture>("res/topDownScene/textures/Package/atlas_16x.png")->
                setSprtieData(
                    {
                        {{16, 112}, {16, 16}},                    
                        {{16, 197}, {16, 32}},                    
                        {{16, 197}, {16, 32}},                    
                    });

            LTE::assetManager::getAsset<LTE::texture>("res/topDownScene/textures/PIPOYA FREE RPG Character Sprites NEKONIN/pipo-nekonin011.png")->
                setSprtieData({32, 32});
            

            LTE::tilemap *map = new LTE::tilemap({1000, 1000}, {100, 100}, 6, sceneId);

            for(int x = 1; x < 9; x++)
                for(int y = 1; y < 9; y++)
                        map->addTile(
                                [=](LTE::tilemap::tileBuilder *tileBuild)
                                {
                                    tileBuild->
                                        setTileMatrial(new LTE::material("res/topDownScene/textures/Package/atlas_16x.png"))->
                                        setLayer(0)->
                                        setTilePostion({x, y});
                                }
                        );

            for(int i = 1; i < 9; i++)
            {
                map->addTile(
                        [=](LTE::tilemap::tileBuilder *tileBuild)
                        {
                            tileBuild->
                                setTileMatrial(new LTE::material("res/topDownScene/textures/Package/atlas_16x.png"))->
                                setLayer(0)->
                                setTilePostion({0, i});
                        }
                );

                map->addTile(
                        [=](LTE::tilemap::tileBuilder *tileBuild)
                        {
                            tileBuild->
                                setTileMatrial(new LTE::material("res/topDownScene/textures/Package/atlas_16x.png"))->
                                setLayer(0)->
                                setTilePostion({9, i});
                        }
                );


                map->addTile(
                        [=](LTE::tilemap::tileBuilder *tileBuild)
                        {
                            tileBuild->
                                setTileMatrial(new LTE::material("res/topDownScene/textures/Package/atlas_16x.png", 2))->
                                setLayer(0)->
                                setTilePostion({i, 0});
                        }
                );

                map->addTile(
                        [=](LTE::tilemap::tileBuilder *tileBuild)
                        {
                            tileBuild->
                                setTileMatrial(new LTE::material("res/topDownScene/textures/Package/atlas_16x.png", 1))->
                                setLayer(0)->
                                setTilePostion({i, 9});
                        }
                );
            }


            map->addTile(
                    [=](LTE::tilemap::tileBuilder *tileBuild)
                    {
                        tileBuild->
                            setTileMatrial(new LTE::material("res/topDownScene/textures/PIPOYA FREE RPG Character Sprites NEKONIN/pipo-nekonin011.png", 1, 3))->
                            setLayer(1)->
                            setTilePostion({5, 5})->
                            AddCompponnetToTile(new player());
                    }
            );
        }

        

        void TearDown() 
        { 
            LTE::app::close();
        }
};



TEST_F(topDownGame, topDownScene)
{
    try
    {    /* code */
        LTE::app::run();
    }
    catch(const std::exception& e)
    {
        LAUGHTALE_ENGINR_LOG_FATAL(e.what());
    }
    catch(std::exception* e)
    {
        LAUGHTALE_ENGINR_LOG_FATAL(e->what());
    }
}
