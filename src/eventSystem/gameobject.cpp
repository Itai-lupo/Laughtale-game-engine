#include "gameobject.h"
#include <stdlib.h>
#include "LTEError.h"
#include "logger.h"


namespace LTE
{
    gameObjectsManger::~gameObjectsManger()
    {
        gameObjects.clear();
    }

    std::shared_ptr<gameObject> gameObjectsManger::addGameObject(const std::string& name)
    {
        std::shared_ptr<gameObject> res = std::make_shared<gameObject>(nextGameObjectId, name);
        gameObjects.push_back(res);
        nextGameObjectId++;
        return res;
    }

    std::shared_ptr<gameObject> gameObjectsManger::getGameObjectByName(const std::string& name)
    {
        std::shared_ptr<gameObject>e = nullptr;
        for (uint64_t i = 0; i < gameObjects.size(); i++)
        {
            if(gameObjects[i]->getName()  == name)
                return gameObjects[i];
        }
        
        throw GameObjectNotFoundException("game object with name:" + name + "wasn't found");
        return  NULL;
        
    }

    std::shared_ptr<gameObject> gameObjectsManger::getGameObjectById(gameObjectId id)
    {
        std::shared_ptr<gameObject>e = nullptr;
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
                std::shared_ptr<gameObject>e = gameObjects[i]; 
                gameObjects.erase(gameObjects.begin() + i);
            }
        }
        
    }

    void gameObjectsManger::forEachObject(std::function<void(std::shared_ptr<gameObject>)> callback)
    {
        for (uint64_t i = 0; i < gameObjects.size(); i++)
        {
            callback(gameObjects[i]);
        }
    }

}