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
            [=](std::weak_ptr<LTE::gameObject> g) -> bool { return g.lock() && g.lock()->getId() == id; }
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
                        if(*squreColliders[i].lock()->getComponent<squreCollider>().get() == *squreColliders[j].lock()->getComponent<squreCollider>().get())
                        {
                            collisionData *IToJ = new collisionData(squreColliders[i].lock()->getId(), squreColliders[j].lock());
                            collisionData *JToI = new collisionData(squreColliders[j].lock()->getId(), squreColliders[i].lock());
                            sceneManger::getScene(parentScene)->getEventsManger()->trigerEvent(IToJ, sceneEventsType::collision);
                            sceneManger::getScene(parentScene)->getEventsManger()->trigerEvent(JToI, sceneEventsType::collision);
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
