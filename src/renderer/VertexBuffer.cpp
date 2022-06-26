#include "VertexBuffer.h"
#include "graphicsContext.h"

namespace LTE
{
    void VertexBuffer::checkIfExitesInThisContextAndInitIfNot()
    {
        if(data.get() != NULL && graphicsContext::getMeshFactory() != NULL)
            return;
        data.reset(graphicsContext::getMeshFactory()->createVertexBuffer(this));
    }   
} 
