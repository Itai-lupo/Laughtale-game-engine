#pragma once
#include "renderApi.h"
#include "scene.h"

#include <map>
#include <set>

namespace LTE
{
    class coreRenderer
    {
        protected:
            scene *Scene;

            renderApi *renderPipLine;

        public:                
            coreRenderer(scene *Scene, renderApi *renderPipLine): 
            Scene(Scene), renderPipLine(renderPipLine)
            {

            }


            virtual void renderScene() = 0;
    };
    
    
}
