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
        gameObjects.clear();
        nextGameObjectId = 1;
    }

    gameObjectId gameObjectsManger::addGameObject(std::function<void(gameObjectBuilder *Builder)> buildGameObject, sceneId parentScene)
    {
        builder->reset(parentScene);
        buildGameObject(builder);
        std::shared_ptr< LTE::gameObject>res = builder->build(nextGameObjectId);
        gameObjects.push_back(res);
        nextGameObjectId++;
        return res->getId();
    }

    std::shared_ptr< LTE::gameObject>gameObjectsManger::getGameObjectByName(const std::string& name)
    {
        std::shared_ptr< LTE::gameObject>e = nullptr;
        for (uint64_t i = 0; i < gameObjects.size(); i++)
        {
            if(gameObjects[i]->getName()  == name)
                return gameObjects[i];
        }
        
        throw GameObjectNotFoundException("game object with name:" + name + "wasn't found");
        return  NULL;
        
    }

    std::shared_ptr< LTE::gameObject>gameObjectsManger::getGameObjectById(gameObjectId id)
    {
        std::shared_ptr< LTE::gameObject>e = nullptr;
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
                std::shared_ptr< LTE::gameObject>e = gameObjects[i]; 
                gameObjects.erase(gameObjects.begin() + i);
                e->end();
            }
        }
        
    }
}