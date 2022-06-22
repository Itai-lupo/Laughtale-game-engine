#include <iostream>
#include <string>

using namespace std;

#include "glad/glad.h"
#include "handleOpenGlErrors.h"
#include "logger.h"

void GLClearErrors()
{
    while(glGetError() != GL_NO_ERROR);
}

std::string GL_TranslateError (GLenum error)
{
#define GL_ERROR_TRANSLATE(e) case e: return #e;
    switch (error) {
        GL_ERROR_TRANSLATE(GL_INVALID_ENUM)
        GL_ERROR_TRANSLATE(GL_INVALID_VALUE)
        GL_ERROR_TRANSLATE(GL_INVALID_OPERATION)
        GL_ERROR_TRANSLATE(GL_OUT_OF_MEMORY)
        GL_ERROR_TRANSLATE(GL_NO_ERROR)
        GL_ERROR_TRANSLATE(GL_STACK_OVERFLOW)
        GL_ERROR_TRANSLATE(GL_STACK_UNDERFLOW) 
        GL_ERROR_TRANSLATE(GL_INVALID_FRAMEBUFFER_OPERATION)
        default:
            return "UNKNOWN";
    }
#undef GL_ERROR_TRANSLATE
}

void GLCheckError(const char *function, const char *file, int line)
{
    GLenum error;
    while((error = glGetError()) != GL_NO_ERROR)
    {
        LAUGHTALE_ENGINR_LOG_INFO(
            "[OpenGL error] (" << GL_TranslateError(error) << ": " << error << "): " << function << " " << file <<  ":" << line);
    }
    
}
