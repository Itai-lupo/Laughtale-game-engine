#include "texture.hpp"
#include "graphicsContext.hpp"

namespace LTE
{
    void texture::checkIfExitesInThisContextAndInitIfNot()
    {
        if(data.get() != NULL && graphicsContext::getMeshFactory() != NULL)
            return;
        data.reset(graphicsContext::getMeshFactory()->createTexture(this));
    }   
} 
