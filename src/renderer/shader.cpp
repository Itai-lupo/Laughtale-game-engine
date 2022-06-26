#include "shader.h"
#include "graphicsContext.h"

namespace LTE
{
    void shader::checkIfExitesInThisContextAndInitIfNot()
    {
        if(data.get() != NULL && graphicsContext::getMeshFactory() != NULL)
            return;
        data.reset(graphicsContext::getMeshFactory()->createShader(this));
    }   
} 
