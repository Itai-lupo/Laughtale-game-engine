#include "vertexArray.hpp"
#include "graphicsContext.hpp"

namespace LTE
{
    void vertexArray::checkIfExitesInThisContextAndInitIfNot()
    {
        if(data.get() != NULL && graphicsContext::getMeshFactory() != NULL)
            return;
        data.reset(graphicsContext::getMeshFactory()->createVertexArray(this));
    }   
} 
