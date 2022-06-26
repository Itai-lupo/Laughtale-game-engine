#include "openGLVertexBuffer.h"
#include "glad/glad.h"
#include "handleOpenGlErrors.h"
#include "logger.h"

namespace LTE
{
    void OpenGLVertexBuffer::init()
    {
        GL_CALL(glGenBuffers(1, &RendererID));
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, RendererID));
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, parentContainer->getSize(), parentContainer->getData(), GL_STATIC_DRAW));
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &RendererID);
    }

    void OpenGLVertexBuffer::setVBData()
    {
        changeId = parentContainer->getChangeId();
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, RendererID));
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, parentContainer->getSize(), parentContainer->getData(), GL_STATIC_DRAW));
    }

    void OpenGLVertexBuffer::bind()
    {
        if(changeId != parentContainer->getChangeId())
            setVBData();
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, RendererID));
    }

    void OpenGLVertexBuffer::unbind()
    {
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
}