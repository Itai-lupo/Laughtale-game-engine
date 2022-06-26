#include "vertexArray.h"
#include "graphicsContext.h"

namespace LTE
{
    void vertexArray::checkIfExitesInThisContextAndInitIfNot()
    {
        if(data.get() != NULL && graphicsContext::getMeshFactory() != NULL)
            return;
        data.reset(graphicsContext::getMeshFactory()->createVertexArray(this));
    }   
} 
