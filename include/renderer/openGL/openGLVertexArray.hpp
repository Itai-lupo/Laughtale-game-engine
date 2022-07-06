#pragma once
#include "vertexArray.hpp"
#include "VertexBuffer.hpp"
#include "openGLBase.hpp"

namespace LTE
{
    class openGLVertexArray: public vertexArrayRenderApi, public openGLBase
    {
        private:
            uint32_t rendererId = 0;
            VertexBuffer *vb;
        
            void setBuffer();
        
        public:
            openGLVertexArray(vertexArray *parentContainer): vertexArrayRenderApi(parentContainer){}
            ~openGLVertexArray();

            virtual void init() override;
            virtual void bind() override;
            virtual void unbind() override;
    };
} 
