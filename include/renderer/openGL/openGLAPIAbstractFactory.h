#pragma once
#include "graphicsAPIAbstractFactory.h"
#include "openGLAbsrtactFactory.h"
#include "openGLrenderApi.h"


namespace LTE
{
    class openGLAPIAbstractFactory: public graphicsAPIAbstractFactory
    {
        public:
            virtual meshAbsrtactFactory *createMeshAbsrtactFactory()
            {
                return new openGLAbsrtactFactory();
            }
            
            virtual renderApi *createRenderApi() 
            {
                return new openGLRenderApi();
            }
    };
};