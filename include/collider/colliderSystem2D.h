#pragma once
#include "squreCollider.h"

#include <vector>
#include <thread>
#include <map>

namespace LTE
{
    class colliderSystem2D
    {
        private:
            std::vector<std::weak_ptr< LTE::gameObject>> squreColliders;
            std::thread *t;
            sceneId parentScene;
        public:
            colliderSystem2D(sceneId parentScene):parentScene(parentScene){}
            void init();
            void close();

            void addSqureCollider(std::weak_ptr< LTE::gameObject>collider){ squreColliders.push_back(collider); }
            void removeSqureCollider(gameObjectId);

            void checkCollision();

    };
} 
