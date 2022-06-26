#pragma once
#include <vector>
#include <boost/thread.hpp>
#include <atomic>


#include "core.h"

namespace LTE
{
    class indexBuffer;

    class indexBufferRenderApi
    {
        protected:
            indexBuffer *parentContainer;
            std::atomic<int> changeId = 0;

        public:
            virtual ~indexBufferRenderApi() = default;

            indexBufferRenderApi(indexBuffer *parentContainer): parentContainer(parentContainer){}
        

            virtual void init() = 0;
            virtual void bind() = 0;
            virtual void unbind() = 0;
    };

    class indexBuffer
    {
        private:
            uint32_t *indices;
            uint32_t count;
            std::atomic<unsigned int> changeId = 0;
            
            boost::thread_specific_ptr<indexBufferRenderApi> data;

            void checkIfExitesInThisContextAndInitIfNot();

        public:
            indexBuffer(uint32_t *indices, uint32_t count): indices(indices), count(count)
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


            unsigned int getCount() 
            { 
                return count; 
            }

            unsigned int *geIndices()
            {
                return indices;
            }

            unsigned int getChangeId()
            {
                return changeId;
            }

            void setData(unsigned int *ib, unsigned int count)
            {
                indices = ib;
                this->count = count;
                changeId++;
            }



    };
}
