#include "texture.h"
#include "graphicsContext.h"

namespace LTE
{
    void texture::checkIfExitesInThisContextAndInitIfNot()
    {
        if(data.get() != NULL && graphicsContext::getMeshFactory() != NULL)
            return;
        data.reset(graphicsContext::getMeshFactory()->createTexture(this));
    }   
} 
