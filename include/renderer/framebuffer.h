#pragma once
#include "core.h"
#include "texture.h"

#include <boost/thread.hpp>

namespace LTE
{
    typedef uint32_t colorAttachmentSlot;
    
    class framebuffer;

    class framebufferRenderApi
    {
        protected:
            framebuffer *parentContainer;
            std::atomic<unsigned int> changeId = 0;

        public:
            framebufferRenderApi(framebuffer *parentContainer): parentContainer(parentContainer){}
            virtual ~framebufferRenderApi() = default;
            
            virtual void init() = 0;
            virtual void bind() = 0;
            virtual void unbind() = 0;

    };

    class framebuffer
    {
        private:
            boost::thread_specific_ptr<framebufferRenderApi> data;
            void checkIfExitesInThisContextAndInitIfNot();

            uint32_t width, hight;

            std::map<colorAttachmentSlot, texture*> colorAttachmens;
            texture* depthAttachmen = nullptr;

            std::atomic<unsigned int> changeId = 0;

        public:
            framebuffer(uint32_t width, uint32_t hight): width(width), hight(hight)
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

            void attachColorRenderTarget(texture *attachmentData, colorAttachmentSlot attachmentSlot) 
            {
                colorAttachmens[attachmentSlot] = attachmentData;
                changeId++;
            }

            void setDepthRenderTarget(texture *attachmentData) 
            {
                depthAttachmen = attachmentData;
                changeId++;
            }

            void resize(uint32_t width, uint32_t hight)
            {
                this->width = width;
                this->hight = hight;
                changeId++;
            }


            uint32_t getWidth()
            {
                return width;
            } 

            uint32_t getHight()
            {
                return hight;
            }

            std::map<colorAttachmentSlot, texture*> getColorAttachmens()
            {
                return colorAttachmens;
            }

            texture* getDepthAttachmen()
            {
                return depthAttachmen;
            }

            unsigned int getChangeId()
            {
                return changeId;
            }


    };
}
