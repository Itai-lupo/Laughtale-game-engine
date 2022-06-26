#pragma once
#include "framebuffer.h"
#include "texture.h"
#include "core.h"
#include "openGLBase.h"

#include <map>



namespace LTE
{
    class openGLFramebuffer: public framebufferRenderApi, public openGLBase
    {
        private:
            framebufferId id;

            void rebuild();
        public:
            openGLFramebuffer(framebuffer *parentContainer): framebufferRenderApi(parentContainer){}
            ~openGLFramebuffer();

            virtual void init() override;
            virtual void bind() override;
            virtual void unbind() override;

    };
}
