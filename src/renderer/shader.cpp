#include "shader.hpp"
#include "graphicsContext.hpp"

namespace LTE
{
    void shader::checkIfExitesInThisContextAndInitIfNot()
    {
        if(data.get() != NULL && graphicsContext::getMeshFactory() != NULL)
            return;
        data.reset(graphicsContext::getMeshFactory()->createShader(this));
    }   
} 
