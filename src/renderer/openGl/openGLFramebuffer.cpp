#include "openGLFramebuffer.hpp"
#include <glad/glad.h>
#include "handleOpenGlErrors.hpp"
#include "app.hpp"

namespace LTE
{
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
        if(changeId != parentContainer->getChangeId())
            rebuild();
        GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, id));  
        GL_CALL(glViewport(0, 0,  parentContainer->getWidth(), parentContainer->getHight()));

    }

    void openGLFramebuffer::unbind() 
    {
        GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));  

    }


    void openGLFramebuffer::rebuild()
    {
        changeId = parentContainer->getChangeId();
        
        if(id)
			GL_CALL(glDeleteFramebuffers(1, &id));
        

		GL_CALL(glCreateFramebuffers(1, &id));
		GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, id));

        for( auto& [slot, colorAttachmenData]: parentContainer->getColorAttachmens())
        {
            colorAttachmenData->setDimensions({ parentContainer->getWidth(), parentContainer->getHight()});
			GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot,  (colorAttachmenData->getSamples() > 1)? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, colorAttachmenData->getId(), 0)); // todo: need to add GL_TEXTURE_2D_MULTISAMPLE
        }

        if(parentContainer->getDepthAttachmen())
        {
            parentContainer->getDepthAttachmen()->setDimensions({ parentContainer->getWidth(), parentContainer->getHight()});
            unsigned int outID;
			GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, (parentContainer->getDepthAttachmen()->getSamples() > 1)? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, parentContainer->getDepthAttachmen()->getId(), 0));
        }
            

        LAUGHTALE_ENGINR_CONDTION_LOG_ERROR("Framebuffer is incomplete!", glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    
    }
}
