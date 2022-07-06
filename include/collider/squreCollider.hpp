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
}  