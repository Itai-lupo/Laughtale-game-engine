#pragma once
#include "renderApi.h"

#include <map>
#include <set>

namespace LTE
{
    class coreRenderer
    {
        public:      
            virtual ~coreRenderer() = default;          


            virtual void renderScene(uint32_t width, uint32_t  hight) = 0;
    };
    
    
}
