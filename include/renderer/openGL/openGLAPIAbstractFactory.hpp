#pragma once
#include "graphicsAPIAbstractFactory.hpp"
#include "openGLAbsrtactFactory.hpp"
#include "openGLrenderApi.hpp"


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