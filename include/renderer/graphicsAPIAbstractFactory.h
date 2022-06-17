#pragma once
#include "meshAbsrtactFactory.h"
#include "renderApi.h"


namespace LTE
{
    class graphicsAPIAbstractFactory
    {
        public:
            virtual meshAbsrtactFactory *createMeshAbsrtactFactory() = 0;
            virtual renderApi *createRenderApi() = 0;
    };
};