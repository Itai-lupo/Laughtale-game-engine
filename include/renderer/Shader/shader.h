#pragma once
#include <vector>
#include<string>
#include <glm/glm.hpp>
#include <boost/thread.hpp>

#include "asset.h"
#include "core.h"
#include "component.h"

namespace LTE
{
    class shader;

    class shaderRenderApi
    {        
        protected:
            shader *parentContainer;
        public:
            shaderRenderApi(shader *parentContainer): parentContainer(parentContainer){}
            virtual ~shaderRenderApi() = default;

            virtual void init() = 0;

            virtual void bind() = 0;
            virtual void unbind() = 0;
            virtual void setUniform1i(const std::string& name, int value) = 0;
            virtual void setUniform1f(const std::string& name, float value) = 0;
            virtual void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) = 0;
            virtual void setUniformMat4f(const std::string& name, const glm::mat4& value) = 0;
            virtual void setUniform1iv(const std::string& name, const int* v, int size) = 0;
    };

    class shader: public asset
    {
        private:
            boost::thread_specific_ptr<shaderRenderApi> data;

            void checkIfExitesInThisContextAndInitIfNot();

            std::string vertexSource;
            std::string fragmentSource;

        public:
            shader(const std::string& vertexSource, const std::string& fragmentSource): vertexSource(vertexSource), fragmentSource(fragmentSource)
            {

            }

            void bind()
            {
                checkIfExitesInThisContextAndInitIfNot();
                data->bind();
            }

            void unbind()
            {
                checkIfExitesInThisContextAndInitIfNot();
                data->unbind();
            }

            void setUniform1i(const std::string& name, int value)
            {
                checkIfExitesInThisContextAndInitIfNot();
                data->setUniform1i(name, value);
            }

            void setUniform1f(const std::string& name, float value)
            {
                checkIfExitesInThisContextAndInitIfNot();
                data->setUniform1f(name, value);
            }

            void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
            {
                checkIfExitesInThisContextAndInitIfNot();
                data->setUniform4f(name, v0, v1, v2, v3);
            }

            void setUniformMat4f(const std::string& name, const glm::mat4& value)
            {
                checkIfExitesInThisContextAndInitIfNot();
                data->setUniformMat4f(name, value);
            }

            void setUniform1iv(const std::string& name, const int* v, int size)
            {
                checkIfExitesInThisContextAndInitIfNot();
                data->setUniform1iv(name, v, size);
            }


            std::string getVertexSource()
            {
                return vertexSource;
            }

            std::string getfragmentSource()
            {
                return fragmentSource;
            }


    };
}
