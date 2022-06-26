#pragma once

#include <queue>
#include <atomic>

#include "meshAbsrtactFactory.h"
#include "openGLBase.h"
#include "openGLShader.h"
#include "openGLVertexArray.h"
#include "openGLVertexBuffer.h"
#include "openGLIndexBuffer.h"
#include "openGLTexture.h"
#include "openGLFramebuffer.h"

namespace LTE
{
    class openGLAbsrtactFactory: public meshAbsrtactFactory
    {
        private:
            std::queue<openGLBase*> needToInit;
        public:

            virtual shaderRenderApi *createShader(shader *parentContainer)
            {
                openGLShader *s = new openGLShader(parentContainer);
                s->init();
                return s;
            }

            virtual vertexArrayRenderApi *createVertexArray(vertexArray *parentContainer)
            {
                openGLVertexArray *va = new openGLVertexArray(parentContainer);
                va->init();
                return va;

            }

            virtual VertexBufferRenderApi *createVertexBuffer(VertexBuffer *parentContainer)
            {

                OpenGLVertexBuffer *vb = new OpenGLVertexBuffer(parentContainer);
                vb->init();
                return vb;
            }

            virtual indexBufferRenderApi *createIndexBuffer(indexBuffer *parentContainer)
            {
                openGLIndexBuffer *ib = new openGLIndexBuffer(parentContainer);
                ib->init();
                return ib;

            }

            virtual textureRenderApi *createTexture(texture *parentContainer)
            {
                openGLTexture *t = new openGLTexture(parentContainer);
                t->init();
                return t;

            }

            virtual framebufferRenderApi *createFramebuffer(framebuffer *parentContainer)
            {
                openGLFramebuffer *fbo = new openGLFramebuffer(parentContainer);
                fbo->init();
                return fbo;

            }
    };
}