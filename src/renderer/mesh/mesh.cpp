#include "mesh.h"
#include "core.h"
#include "openGLShader.h"
#include "openGLVertexBuffer.h"
#include "openGLVertexArray.h"
#include "openGLIndexBuffer.h"
#include "materialsManger.h"
#include "material.h"
#include "app.h"
#include "windowManger.h"
#include "glm/glm.hpp"
#include "sceneManger.h"


namespace LTE
{
    void mesh::setIndexBuffer(uint32_t *indices, uint32_t count)
    {
        indices = indices;
        count = count;    
    }

    void mesh::setVertexBuffer(float *vertexs, uint32_t size)
    {
        vertexs = vertexs;
        size = size; 
    }

    void mesh::setShaderName(const std::string& shaderName)
    {
        shaderToUse = shaderName;
        assetManager::loadAssetFromFile(shaderName);

    }

    std::string mesh::getShaderName()
    {
        return  shaderToUse;
    }

    int mesh::getSize()
    {
        return  size;
    }

    float *mesh::getVB()
    {
        return vertexs;
    }

    uint32_t* mesh::getIB()
    {
        return indices; 
    }

    uint32_t mesh::getCount()
    {
        return count;
    }
}