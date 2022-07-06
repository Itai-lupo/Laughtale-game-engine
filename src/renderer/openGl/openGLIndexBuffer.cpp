#include "openGLIndexBuffer.hpp"
#include "handleOpenGlErrors.hpp"
#include <glad/glad.h>

namespace LTE
{
    void openGLIndexBuffer::init()
    {
        GL_CALL(glGenBuffers(1, &RendererID));
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID));
        GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, parentContainer->getCount() * sizeof(unsigned int), parentContainer->geIndices(), GL_STATIC_DRAW));
    }

    openGLIndexBuffer::~openGLIndexBuffer()
    {
        GL_CALL(glDeleteBuffers(1, &RendererID));
    }

    void openGLIndexBuffer::bind()
    {
        if(changeId != parentContainer->getChangeId())
            setData();
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID));
    }

    void openGLIndexBuffer::unbind()
    {
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));    
    }

    void openGLIndexBuffer::setData()
    {
        changeId = parentContainer->getChangeId();
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID));
        GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, parentContainer->getCount() * sizeof(unsigned int), parentContainer->geIndices(), GL_STATIC_DRAW));
    }

}