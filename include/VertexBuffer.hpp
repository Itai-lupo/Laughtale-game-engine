#pragma once
#include <vector>
#include <boost/thread.hpp>

#include "core.hpp"
#include "logger.hpp"

namespace LTE
{
    class VertexBuffer;

    struct VertexBufferElement{
        unsigned int type;
        unsigned int count;
        unsigned char normalized; 
        unsigned int sizeOfType;

        VertexBufferElement(unsigned int type, unsigned int count, unsigned char normalized, unsigned int sizeOfType):
            type(type), count(count), normalized(normalized), sizeOfType(sizeOfType){}
    };

    class VertexBufferLayout
    {
        private:
            std::vector<VertexBufferElement> elements;
            unsigned int stride = 0;
        public:
            VertexBufferLayout()
                : stride(0){}

            inline VertexBufferLayout *push(const VertexBufferElement& ElementToPush)
            {
                stride += ElementToPush.sizeOfType * ElementToPush.count;
                elements.push_back(ElementToPush);
                return this;
            }

            inline const std::vector<VertexBufferElement>& getElements() { return elements; }
            inline unsigned int GetStride() { return stride; };
    };

    class VertexBufferRenderApi 
    {
        protected:
            VertexBuffer *parentContainer;
            std::atomic<int> changeId = 0;

        public:
            virtual ~VertexBufferRenderApi() = default;
            VertexBufferRenderApi(VertexBuffer *parentContainer): parentContainer(parentContainer){}

            virtual void init() = 0;
            virtual void bind() = 0;
            virtual void unbind() = 0;


    };

    class VertexBuffer
    {
        private:
            const void *vertexs;
            unsigned int size;
            VertexBufferLayout *VBLayout;

            boost::thread_specific_ptr<VertexBufferRenderApi> data;
            std::atomic<unsigned int> changeId = 0;

            void checkIfExitesInThisContextAndInitIfNot();

        public:
            VertexBuffer(float *vertexs, uint32_t size): vertexs(vertexs), size(size), VBLayout(new VertexBufferLayout())
            {

            }
            
            void setData(const void *data, uint32_t size)
            {
                vertexs = data;
                this->size = size;
                changeId++;
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

            const std::vector<VertexBufferElement> getElements() 
            { 
                return VBLayout->getElements(); 
            }
            
            unsigned int GetStride() 
            { 
                return VBLayout->GetStride(); 
            }
            
            void pushElement(const VertexBufferElement& ElementToPush) 
            {  
                VBLayout->push(ElementToPush); 
            }

            unsigned int getSize()
            {
                return size;
            }

            const void *getData()
            {
                return vertexs;
            }

            unsigned int getChangeId()
            {
                return changeId;
            }

    };
}