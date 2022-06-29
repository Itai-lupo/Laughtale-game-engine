#pragma once
#include <functional>
#include <vector>
#include "core.h"

namespace LTE
{
    class gameObject;
    class component
    {
        protected:
            sceneId parentScene;
            gameObjectId parentId;
        public:
            virtual ~component() = default;
            virtual void init(gameObject *parent) = 0;
            virtual void end() = 0;

            void setParent(gameObjectId parentId, sceneId parentScene)
            {
                this->parentScene = parentScene;
                this->parentId = parentId;
            }

            gameObjectId getParentId(){return parentId; }
    };

}