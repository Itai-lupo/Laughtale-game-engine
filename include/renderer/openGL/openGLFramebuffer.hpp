#pragma once
#include "framebuffer.hpp"
#include "texture.hpp"
#include "core.hpp"
#include "openGLBase.hpp"

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
