#pragma once
#include "core.h"
#include "VertexBuffer.h"

#include <boost/thread.hpp>

namespace LTE
{
    class vertexArray;

    class vertexArrayRenderApi
    {
        protected:
            vertexArray *parentContainer;
        public:
            vertexArrayRenderApi(vertexArray *parentContainer): parentContainer(parentContainer){}
            virtual ~vertexArrayRenderApi() = default;
            virtual void init() = 0;

            virtual void bind() = 0;
            virtual void unbind() = 0;
    };

    class vertexArray
    {
        private:
            VertexBuffer *vb;
            boost::thread_specific_ptr<vertexArrayRenderApi> data;

            void checkIfExitesInThisContextAndInitIfNot();

        public:
            vertexArray(VertexBuffer *vb): vb(vb)
            {

            }

            void setBuffer(VertexBuffer *vb)
            {
                this->vb = vb;
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

            VertexBuffer *getVB()
            {
                return vb;
            }

    };
} 
