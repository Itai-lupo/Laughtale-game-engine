#include "gameobject.h"
#include <stdlib.h>
#include "LTEError.h"
#include "logger.h"
namespace LTE
{

    gameObjectsManger::gameObjectsManger()
    {
        builder = new gameObjectBuilder();
    }

    gameObjectsManger::~gameObjectsManger()
    {
        for(auto& t: gameObjects)
            delete t;
        gameObjects.clear();
        nextGameObjectId = 1;
    }

    gameObjectId gameObjectsManger::addGameObject(std::function<void(gameObjectBuilder *Builder)> buildGameObject, sceneId parentScene)
    {
        builder->reset(parentScene);
        buildGameObject(builder);
        gameObject *res = builder->build(nextGameObjectId);
        gameObjects.push_back(res);
        nextGameObjectId++;
        return res->getId();
    }

    gameObject *gameObjectsManger::getGameObjectByName(const std::string& name)
    {
        gameObject *e = nullptr;
        for (uint64_t i = 0; i < gameObjects.size(); i++)
        {
            if(gameObjects[i]->getName()  == name)
                return gameObjects[i];
        }
        
        throw GameObjectNotFoundException("game object with name:" + name + "wasn't found");
        return  NULL;
        
    }

    gameObject *gameObjectsManger::getGameObjectById(gameObjectId id)
    {
        gameObject *e = nullptr;
        for (uint64_t i = 0; i < gameObjects.size(); i++)
        {
            if(gameObjects[i]->getId()  == id)
                return gameObjects[i];
        }
        
        throw new GameObjectNotFoundException("game object with id: " + std::to_string(id) + " wasn't found");
        return  NULL;
    }

    void gameObjectsManger::removeGameObjectById(gameObjectId id)
    {
        for (uint64_t i = 0; i < gameObjects.size(); i++)
        {
            if(gameObjects[i]->getId()  == id)
            {
                gameObject *e = gameObjects[i]; 
                gameObjects.erase(gameObjects.begin() + i);
                e->end();
                delete e;
            }
        }
        
    }
}