#pragma once
#include "openGLBase.hpp"
#include "indexBuffer.hpp"

namespace LTE
{
    class openGLIndexBuffer : public indexBufferRenderApi, public openGLBase
    {
        private:
            uint32_t RendererID;
            void setData();
        
        public:
            openGLIndexBuffer(indexBuffer *parentContainer)
                :indexBufferRenderApi(parentContainer){}
            ~openGLIndexBuffer();
            virtual  void init() override;
            virtual  void bind() override;
            virtual  void unbind() override;


    };
}