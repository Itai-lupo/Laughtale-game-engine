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
            std::vector<gameObject *> squreColliders;
            std::thread *t;
            sceneId parentScene;
        public:
            colliderSystem2D(sceneId parentScene):parentScene(parentScene){}
            void init();
            void close();

            void addSqureCollider(gameObject *collider){ squreColliders.push_back(collider); }
            void removeSqureCollider(gameObjectId);

            void checkCollision();

    };
} 
