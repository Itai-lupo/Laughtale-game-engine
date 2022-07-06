#pragma once
#include "meshAbsrtactFactory.hpp"
#include "renderApi.hpp"


namespace LTE
{
    class graphicsAPIAbstractFactory
    {
        public:
            virtual meshAbsrtactFactory *createMeshAbsrtactFactory() = 0;
            virtual renderApi *createRenderApi() = 0;
    };
};