#include "indexBuffer.hpp"
#include "graphicsContext.hpp"

namespace LTE
{
    void indexBuffer::checkIfExitesInThisContextAndInitIfNot()
    {
        if(data.get() != NULL && graphicsContext::getMeshFactory() != NULL)
            return;
        data.reset(graphicsContext::getMeshFactory()->createIndexBuffer(this));
    }   
} 
