#include "handleOpenGlErrors.hpp"
#include "openGLVertexArray.hpp"
#include <glad/glad.h>

#include "logger.hpp"
#include <string>

namespace LTE
{

    openGLVertexArray::~openGLVertexArray()
    {
        GL_CALL(glDeleteVertexArrays(1, &rendererId));
    }

    void openGLVertexArray::init()
    {
        GL_CALL(glGenVertexArrays(1, &rendererId));
        setBuffer();
    }

    void openGLVertexArray::setBuffer()
    {
        vb = parentContainer->getVB();
        LAUGHTALE_ENGINR_CONDTION_LOG_FATAL("no vertex buffer layout", vb->getElements().size() == 0);
        
        
        bind();
        const auto& elements = vb->getElements();

        vb->bind();
        unsigned long i = 0, offset = 0;
        for(const auto& element : elements)
        {
            GL_CALL(glEnableVertexAttribArray(i));
            GL_CALL(glVertexAttribPointer(i, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE,  vb->GetStride(), (const void*)offset));
            offset += element.count * element.sizeOfType;
            i++;
        }
    }

    void openGLVertexArray::bind()
    {
        if(vb != parentContainer->getVB())
            setBuffer();
        GL_CALL(glBindVertexArray(rendererId));
    }

    void openGLVertexArray::unbind()
    {
        GL_CALL(glBindVertexArray(0));
    }
}

