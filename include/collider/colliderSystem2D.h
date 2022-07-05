#pragma once
#include "squreCollider.h"

#include <vector>
#include <thread>
#include <map>

namespace LTE
{
    class scene;
    class colliderSystem2D
    {
        private:
            std::thread *t;
            scene *parentScene;
            std::map<gameObjectId, std::vector<std::weak_ptr<gameObject>>> activeCollisions;

            void checkCollision();
            bool isEqual(std::shared_ptr<gameObject> a, std::shared_ptr<gameObject> b);
            bool checkXBonds(float selfRight, float selfLeft, float otherRight, float otherLeft);
            bool checkYBonds(float selfTop, float selfBottom, float otherTop, float otherBottom);

        public:
            colliderSystem2D(scene *parentScene);
            ~colliderSystem2D();


    };
} 
