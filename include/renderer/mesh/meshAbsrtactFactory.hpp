#pragma once
#include "shader.hpp"
#include "vertexArray.hpp"
#include "VertexBuffer.hpp"
#include "indexBuffer.hpp"
#include "texture.hpp"
#include "framebuffer.hpp"

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