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


            virtual void renderScene() = 0;
    };
    
    
}
