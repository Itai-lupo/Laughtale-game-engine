#pragma once
#include "core.h"
#include "texture.h"

namespace LTE
{
    typedef uint32_t colorAttachmentSlot;
    
    class framebuffer
    {
        protected:
            framebufferId id;
            
        public:
            virtual ~framebuffer() = default;
            
            virtual void init() = 0;
            virtual void bind() = 0;
            virtual void unbind() = 0;

            virtual void attachColorRenderTarget(texture *attachmentData, colorAttachmentSlot attachmentSlot) = 0;
            virtual void setDepthRenderTarget(texture *attachmentData) = 0;

            virtual void resize(uint32_t width, uint32_t hight) = 0;
        
            framebufferId getId(){ return id; }

    };
}
