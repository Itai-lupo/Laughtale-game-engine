#pragma once
#include "component.h"
#include "core.h"
#include "gameobject.h"
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