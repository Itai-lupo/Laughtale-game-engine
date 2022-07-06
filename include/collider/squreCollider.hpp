#pragma once
#include "component.hpp"
#include "core.hpp"
#include "gameobject.hpp"
#include <vector>

namespace LTE
{
    class squreCollider: public component
    {
        private:
            
        public:
            squreCollider(){}
            ~squreCollider(){}

            virtual std::string getName() override
            { 
                return "squreCollider";
            }

            virtual void displayComponentProprties() override
            {

            }
    };

    class squreColliderFactory: public componentAbstractFactory
    {
        public:
            virtual ~squreColliderFactory() = default;

            virtual std::shared_ptr<component> createComponent() override
            {
                return std::make_shared<squreCollider>();
            }
    };
}  