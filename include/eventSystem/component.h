#pragma once
#include <functional>
#include <vector>
#include "core.h"
#include <string>

namespace LTE
{
    class gameObject;
    class component
    {
        protected:
            sceneId parentScene;
            gameObjectId parentId;
        public:
            component(){}
            virtual ~component() = default;
            virtual void init(std::shared_ptr<LTE::gameObject>) = 0;
            virtual void end() = 0;

            void setParent(gameObjectId parentId, sceneId parentScene)
            {
                this->parentScene = parentScene;
                this->parentId = parentId;
            }

            virtual std::string getName() = 0;
            virtual void displayComponentProprties() = 0;

            gameObjectId getParentId(){return parentId; }
    };

}