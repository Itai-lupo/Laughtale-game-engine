#pragma once 
#include "openGLBase.h"
#include "shader.h"
#include <unordered_map>
#include <glm/glm.hpp>


namespace LTE
{

    class openGLShader : public shaderRenderApi, public openGLBase
    {
        private:
                std::unordered_map<std::string, int> m_UniformLoctionCache;
                uint32_t rendererID = 0;


                unsigned int compileShader(unsigned int type, const std::string& source);
                void createShader();
                int GetUniformLocation(const std::string& name);

        public:
            openGLShader(shader *parentContainer): shaderRenderApi(parentContainer){}

            ~openGLShader();

            virtual void init() override;
            virtual void bind() override;
            virtual void unbind() override; 
            virtual void setUniform1i(const std::string& name, int value) override;
            virtual void setUniform1f(const std::string& name, float value) override;
            virtual void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) override;
            virtual void setUniformMat4f(const std::string& name, const glm::mat4& value) override;
            virtual void setUniform1iv(const std::string& name, const int* v, int size) override;

    };
}