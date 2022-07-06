#include "VertexBuffer.hpp"
#include "graphicsContext.hpp"

namespace LTE
{
    void VertexBuffer::checkIfExitesInThisContextAndInitIfNot()
    {
        if(data.get() != NULL && graphicsContext::getMeshFactory() != NULL)
            return;
        data.reset(graphicsContext::getMeshFactory()->createVertexBuffer(this));
    }   
} 
