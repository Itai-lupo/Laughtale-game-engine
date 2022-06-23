#pragma once
#include "renderApi.h"
#include "vertexArray.h"
#include "shader.h"
#include "coreCamera.h"
#include "mesh.h"
#include "scene.h"
#include "shaderRenderBuffer.h"

#include "coreRenderer.h"

#include <map>
#include <set>

namespace LTE
{
    class simpleQuadRenderer: public coreRenderer
    {
        private:
            shader *s;
            indexBuffer *indicesToRender;
            VertexBuffer *vertexBuffer;
            vertexArray *vertexArray;

            std::string textureName;

            float squrePostions[20] = 
            {
                -1.0,   1.0f, 0.0f, 0, 1,
                -1.0,  -1.0f, 0.0f, 0, 0,
                1.0,  -1.0f,  0.0f, 1, 0,
                1.0,   1.0f,  0.0f, 1, 1
            };


            unsigned int squreIndices[6] = 
            {
                0, 1, 2,
                0, 3, 2,
            };
            

        public:                
            simpleQuadRenderer(const std::string& textureName, renderApi *renderPipLine);

            virtual void renderScene();
    };
    
    
}
