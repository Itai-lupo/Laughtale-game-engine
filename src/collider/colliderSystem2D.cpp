#include "colliderSystem2D.h"
#include "collisionData.h"
#include "app.h"
#include "sceneManger.h"

#include <algorithm>

namespace LTE
{
    
    void colliderSystem2D::init()
    {
        t = new std::thread(&colliderSystem2D::checkCollision, this);

    }
    
    void colliderSystem2D::close()
    {
        t->join();
    }

    void colliderSystem2D::removeSqureCollider(gameObjectId id)
    {
        squreColliders.erase(std::remove_if(
            squreColliders.begin(),
            squreColliders.end(),
            [=](gameObject *g) -> bool { return g->getId() == id; }
        ));
    }

    void colliderSystem2D::checkCollision()
    {
        while (!app::isRuning){}
        
        while (app::keepRunning)
        {
            for (uint32_t i = 0; i < squreColliders.size(); i++)
            {
                for (uint32_t j = i + 1; j < squreColliders.size(); j++)
                {
                    try
                    {
                        if(*squreColliders[i]->getComponent<squreCollider>() == *squreColliders[j]->getComponent<squreCollider>())
                        {
                            collisionData *IToJ = new collisionData(squreColliders[i]->getId(), squreColliders[j]);
                            collisionData *JToI = new collisionData(squreColliders[j]->getId(), squreColliders[i]);
                            sceneManger::getScene(parentScene)->getEventsManger()->trigerEvent(IToJ, sceneEventsType::collision);
                            // sceneManger::getScene(parentScene)->getEventsManger()->trigerEvent(JToI, sceneEventsType::collision);
                            delete IToJ;
                            delete JToI;
                        }
                        /* code */
                    }
                    catch(ComponentNotFoundException* e)
                    {
                        
                    }
                    
                }
                
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
        
    }

} 
