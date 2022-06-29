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

    float *mesh::getVertices()
    {
        transform* trans =  sceneManger::getScene(parentScene)->getGameObjectById(parentId)->getTransform();
        float temp[size];
        for(int i = 0; i < size ; i += 3)
        {
            glm::vec4 t = glm::vec4(vertexs[i], vertexs[i + 1], vertexs[i + 2], 1.0f);
            t = glm::translate(glm::mat4(1.0f), trans->getPostion()) * 
            glm::rotate(glm::mat4(1.0f), trans->getRotation().x, { 1.0f, 0.0f, 0.0f}) *
            glm::rotate(glm::mat4(1.0f), trans->getRotation().y, { 0.0f, 1.0f, 0.0f}) *
            glm::rotate(glm::mat4(1.0f), trans->getRotation().z, { 0.0f, 0.0f, 1.0f}) *
            glm::scale(glm::mat4(1.0f), trans->getScale()) * t;
            
            temp[i] = t.x;
            temp[i + 1] = t.y;
            temp[i + 2] = t.z;
        }

        return  temp;

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

    void mesh::init(gameObject *parent)
    {
        assetManager::loadAssetFromFile(shaderToUse);
        sceneManger::getScene(parentScene)->pushObjectToRender(parent);
    }

    void mesh::end()
    {
        sceneManger::getScene(parentScene)->removeObjectToRender(parentId);
    }

}