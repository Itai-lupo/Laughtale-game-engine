#pragma once
#include "coreCamera.hpp"
#include "component.hpp"

namespace LTE
{
    class coreCameraControler: public component
    {
        public:
            virtual ~coreCameraControler() = default;
    
            virtual coreCamera *getCamera() = 0;
            virtual float getAspectRatio() = 0;
            virtual void setAspectRatio(float) = 0;

            

            virtual void displayComponentProprties() override
            {
                
            }
    };
}