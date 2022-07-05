#include "colliderSystem2D.h"
#include "collisionData.h"
#include "app.h"
#include "scene.h"

#include <algorithm>

namespace LTE
{
    
    colliderSystem2D::colliderSystem2D(scene *parentScene): parentScene(parentScene)
    {
        t = new std::thread(&colliderSystem2D::checkCollision, this);

    }
    
    colliderSystem2D::~colliderSystem2D()
    {
        t->join();
    }


    bool colliderSystem2D::checkXBonds(float selfRight, float selfLeft, float otherRight, float otherLeft)
    {
        return (
            (selfRight <= otherRight && selfRight >= otherLeft) ||
            (selfLeft <= otherRight && selfLeft >= otherLeft) ||
            (otherRight <= selfRight && otherRight >= selfLeft) ||
            (otherLeft <= selfRight && otherLeft >= selfLeft)
            );
    }  

    bool colliderSystem2D::checkYBonds(float selfTop, float selfBottom, float otherTop, float otherBottom)
    {
        return (
            (selfTop <= otherTop && selfTop >= otherBottom) ||
            (selfBottom <= otherTop && selfBottom >= otherBottom) ||
            (otherTop <= selfTop && otherTop >= selfBottom) ||
            (otherBottom <= selfTop && otherBottom >= selfBottom)
            );
    }

    bool colliderSystem2D::isEqual(std::shared_ptr<gameObject> a, std::shared_ptr<gameObject> b)
    {
        std::shared_ptr<transform> aBonds = a->getTransform();
        std::shared_ptr<transform> bBonds = b->getTransform();

        glm::vec3 aDownRightBonds = aBonds->getPostion() - aBonds->getScale()/2.0f;
        glm::vec3 aUpLeftBonds = aBonds->getPostion() + aBonds->getScale()/2.0f;

        glm::vec3 bDownRightBonds = bBonds->getPostion() - bBonds->getScale()/2.0f;
        glm::vec3 bUpLeftBonds = bBonds->getPostion() + bBonds->getScale()/2.0f;

        bool isWithInBonds =  
            checkYBonds(aUpLeftBonds.y, aDownRightBonds.y, bUpLeftBonds.y, bDownRightBonds.y) &&
            checkXBonds(aUpLeftBonds.x, aDownRightBonds.x, bUpLeftBonds.x, bDownRightBonds.x);
        
        std::vector<std::weak_ptr<gameObject>>::iterator isBInACollisionsList = std::find_if(
            activeCollisions[a->getId()].begin(), 
            activeCollisions[a->getId()].end(),
            [=, this](std::weak_ptr<gameObject> check) -> bool { 
                return a->getId() == check.lock()->getId(); 
            });

        std::vector<std::weak_ptr<gameObject>>::iterator isAInBCollisionsList = std::find_if(
            activeCollisions[b->getId()].begin(), 
            activeCollisions[b->getId()].end(),
            [=, this](std::weak_ptr<gameObject> check) -> bool { 
                return b->getId() == check.lock()->getId(); 
            });
            
            
        bool AlradyInCollisionWith = 
            (isBInACollisionsList != activeCollisions[a->getId()].end()) ||
            (isAInBCollisionsList != activeCollisions[a->getId()].end());
        
            
        if (isWithInBonds && !AlradyInCollisionWith)
        {
            activeCollisions[a->getId()].push_back(b);
            activeCollisions[b->getId()].push_back(a);
            return true;
        }

        if(!isWithInBonds && AlradyInCollisionWith){
            activeCollisions[a->getId()].erase(isBInACollisionsList);
            activeCollisions[b->getId()].erase(isAInBCollisionsList);
        }

        return false;
    }

    void colliderSystem2D::checkCollision()
    {
        while (!app::isRuning){}
        
        while (app::keepRunning)
        {
            std::vector<std::shared_ptr<gameObject>> gameObjectsCash = parentScene->getGameObjectCacheByComponentType<squreCollider>();
            for (uint32_t i = 0; i < gameObjectsCash.size(); i++)
            {
                for (uint32_t j = i + 1; j < gameObjectsCash.size(); j++)
                {
                    
                    if(isEqual(gameObjectsCash[i], gameObjectsCash[j]))
                    {
                        collisionData *IToJ = new collisionData(gameObjectsCash[i]->getId(), gameObjectsCash[j]);
                        collisionData *JToI = new collisionData(gameObjectsCash[j]->getId(), gameObjectsCash[i]);
                        parentScene->getEventsManger()->trigerEvent(IToJ, sceneEventsType::collision);
                        parentScene->getEventsManger()->trigerEvent(JToI, sceneEventsType::collision);
                        delete IToJ;
                        delete JToI;
                    }                    
                }                
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
        
    }

} 
