#pragma once
#include "VertexBuffer.h"
#include "openGLBase.h"

namespace LTE
{

    class OpenGLVertexBuffer: public VertexBufferRenderApi, public openGLBase
    {
        private:
            uint32_t RendererID;
            void setVBData();
        public:
            OpenGLVertexBuffer(VertexBuffer *parentContainer): VertexBufferRenderApi(parentContainer){}
            ~OpenGLVertexBuffer();

            virtual void init() override;
            virtual void bind() override;
            virtual void unbind() override;
    };
}