#include "framebuffer.hpp"
#include "graphicsContext.hpp"

namespace LTE
{
    void framebuffer::checkIfExitesInThisContextAndInitIfNot()
    {
        if(data.get() != NULL && graphicsContext::getMeshFactory() != NULL)
            return;
        data.reset(graphicsContext::getMeshFactory()->createFramebuffer(this));
    }   
} 
