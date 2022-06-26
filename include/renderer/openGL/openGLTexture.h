#pragma once
#include "openGLBase.h"
#include "texture.h"

namespace LTE
{
    class openGLTexture: public textureRenderApi, public openGLBase
    {
        private:
            uint32_t textureFormatToOpenGlFormat(textureFormat format);
        	uint32_t textureFormatToOpenGlDataFormat(textureFormat formatToConvert);

            void uploadDataFromFile();

            textureId id;

        public:
            openGLTexture(texture *parentContainer): textureRenderApi(parentContainer){}
        
            openGLTexture();

            ~openGLTexture();
            virtual void init() override;
            virtual void bind() { bind(1); };

            virtual void bind(int slot) override;
            virtual void unbind() override;
            virtual textureId getId(){ return id; };

        	virtual void setDimensions() override;


    };
}