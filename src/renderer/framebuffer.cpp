#include "framebuffer.h"
#include "graphicsContext.h"

namespace LTE
{
    void framebuffer::checkIfExitesInThisContextAndInitIfNot()
    {
        if(data.get() != NULL && graphicsContext::getMeshFactory() != NULL)
            return;
        data.reset(graphicsContext::getMeshFactory()->createFramebuffer(this));
    }   
} 
