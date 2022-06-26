#pragma once
#include "shader.h"
#include "vertexArray.h"
#include "VertexBuffer.h"
#include "indexBuffer.h"
#include "texture.h"
#include "framebuffer.h"

namespace LTE
{
    class meshAbsrtactFactory
    {
        public:
            virtual shaderRenderApi *createShader(shader *parentContainer) = 0;
            virtual vertexArrayRenderApi *createVertexArray(vertexArray *parentContainer) = 0;
            virtual VertexBufferRenderApi *createVertexBuffer(VertexBuffer *parentContainer) = 0;
            virtual indexBufferRenderApi *createIndexBuffer(indexBuffer *parentContainer) = 0;
            virtual textureRenderApi *createTexture(texture *parentContainer) = 0;
            virtual framebufferRenderApi *createFramebuffer(framebuffer *parentContainer) = 0;
    };
}