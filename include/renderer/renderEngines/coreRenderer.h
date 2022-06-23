#pragma once
#include "renderApi.h"

#include <map>
#include <set>

namespace LTE
{
    class coreRenderer
    {
        protected:

            renderApi *renderPipLine;

        public:                
            coreRenderer(renderApi *renderPipLine):  renderPipLine(renderPipLine)
            {

            }


            virtual void renderScene() = 0;
    };
    
    
}
