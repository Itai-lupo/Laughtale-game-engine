#pragma once
#include "renderApi.hpp"
#include "vertexArray.hpp"
#include "shader.hpp"
#include "coreCamera.hpp"
#include "mesh.hpp"
#include "scene.hpp"
#include "shaderRenderBuffer.hpp"

#include "coreRenderer.hpp"

#include <map>
#include <set>

namespace LTE
{
    class simpleQuadRenderer: public coreRenderer
    {
        private:
            shader *s;
            indexBuffer *indicesToRender;
            VertexBuffer *vertexBufferData;
            vertexArray *vertexArrayData;

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
            simpleQuadRenderer(const std::string& textureName);

            virtual void renderScene(uint32_t width, uint32_t  hight);
    };
    
    
}
