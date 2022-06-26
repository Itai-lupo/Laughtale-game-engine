#include "indexBuffer.h"
#include "graphicsContext.h"

namespace LTE
{
    void indexBuffer::checkIfExitesInThisContextAndInitIfNot()
    {
        if(data.get() != NULL && graphicsContext::getMeshFactory() != NULL)
            return;
        data.reset(graphicsContext::getMeshFactory()->createIndexBuffer(this));
    }   
} 
