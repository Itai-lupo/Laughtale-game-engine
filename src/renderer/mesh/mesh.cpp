#include "mesh.hpp"
#include "core.hpp"
#include "openGLShader.hpp"
#include "openGLVertexBuffer.hpp"
#include "openGLVertexArray.hpp"
#include "openGLIndexBuffer.hpp"
#include "materialsManger.hpp"
#include "material.hpp"
#include "app.hpp"
#include "windowManger.hpp"
#include "glm/glm.hpp"
#include "sceneManger.hpp"


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