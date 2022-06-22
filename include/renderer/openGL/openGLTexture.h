#pragma once
#include "openGLBase.h"
#include "texture.h"

namespace LTE
{
    class openGLTexture: public texture, public openGLBase
    {
        private:
            uint32_t textureFormatToOpenGlFormat(textureFormat format);
        	uint32_t textureFormatToOpenGlDataFormat(textureFormat formatToConvert);

            void uploadDataFromFile();
        public:
            openGLTexture(const std::string& path);
            openGLTexture();

            ~openGLTexture();
            virtual void init() override;
            virtual void bind() { bind(1); };

            virtual void bind(int slot) override;
            virtual void unbind() override;
        	virtual void setDimensions(const glm::vec2 dimensions) override;



    };
}