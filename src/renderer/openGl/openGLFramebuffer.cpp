#include "openGLFramebuffer.h"
#include "glad/glad.h"
#include "handleOpenGlErrors.h"
#include "app.h"

namespace LTE
{
    openGLFramebuffer::openGLFramebuffer(uint32_t width, uint32_t hight):width(width), hight(hight)
    {
    }

    openGLFramebuffer::~openGLFramebuffer()
    {
        GL_CALL(glDeleteFramebuffers(1, &id));  

    }

    void openGLFramebuffer::init() 
    {
        rebuild();

    }

    void openGLFramebuffer::bind() 
    {
        GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, id));  
        GL_CALL(glViewport(0, 0, width, hight));

    }

    void openGLFramebuffer::unbind() 
    {
        GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));  

    }


    void openGLFramebuffer::attachColorRenderTarget(texture *attachmentData, colorAttachmentSlot attachmentSlot) 
    {
        colorAttachmens[attachmentSlot] = attachmentData;
        rebuild();
    }

    void openGLFramebuffer::setDepthRenderTarget(texture *attachmentData) 
    {
        depthAttachmen = attachmentData;
        rebuild();

    }

    void openGLFramebuffer::resize(uint32_t width, uint32_t hight)
    {
        this->width = width;
        this->hight = hight;
        rebuild();
    }

    void openGLFramebuffer::rebuild()
    {
        if (id)
			GL_CALL(glDeleteFramebuffers(1, &id));
        

		GL_CALL(glCreateFramebuffers(1, &id));
		GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, id));

        for( auto& [slot, colorAttachmenData]: colorAttachmens)
        {
            colorAttachmenData->setDimensions({width, hight});
			GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, colorAttachmenData->getId(), 0)); // todo: need to add GL_TEXTURE_2D_MULTISAMPLE
        }

        if(depthAttachmen)
        {
            depthAttachmen->setDimensions({width, hight});
			GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthAttachmen->getId(), 0));
        }
    
    }
}
