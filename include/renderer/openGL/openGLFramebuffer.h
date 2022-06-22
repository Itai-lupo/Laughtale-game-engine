#pragma once
#include "framebuffer.h"
#include "texture.h"
#include "core.h"
#include "openGLBase.h"

#include <map>



namespace LTE
{
    class openGLFramebuffer: public framebuffer, public openGLBase
    {
        private:
            uint32_t width, hight;

            void rebuild();
            std::map<colorAttachmentSlot, texture*> colorAttachmens;
            texture* depthAttachmen = nullptr;

        public:
            openGLFramebuffer(uint32_t width, uint32_t hight);
            ~openGLFramebuffer();

            virtual void init() override;
            virtual void bind() override;
            virtual void unbind() override;

            virtual void attachColorRenderTarget(texture *attachmentData, colorAttachmentSlot attachmentSlot) override;
            virtual void setDepthRenderTarget(texture *attachmentData) override;

            virtual void resize(uint32_t width, uint32_t hight) override;

    };
}
