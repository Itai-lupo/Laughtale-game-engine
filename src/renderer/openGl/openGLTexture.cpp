#pragma once
#include "glad/glad.h"

#include "openGLTexture.h"
#include "stb_image.h"
#include "handleOpenGlErrors.h"


namespace LTE
{
    openGLTexture::~openGLTexture()
    {
        glDeleteTextures(1, &id);
    }

    void openGLTexture::init()
    {

		GL_CALL(glCreateTextures(GL_TEXTURE_2D, 1, &id));
		
		if(parentContainer->getPath() != "")
			uploadDataFromFile();
    }


    void openGLTexture::bind(int slot)
    {
		if (changeId != parentContainer->getChangeId())
			setDimensions();
		
		GL_CALL(glBindTextureUnit(slot, id));
    }
    
    void openGLTexture::unbind()
    {
        GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
    }

	void openGLTexture::setDimensions()
	{		
		changeId = parentContainer->getChangeId();
        glDeleteTextures(1, &id);
		GL_CALL(glCreateTextures(GL_TEXTURE_2D, 1, &id));

		GL_CALL(glTextureStorage2D(id, 1, textureFormatToOpenGlFormat(parentContainer->getFormat()), parentContainer->getWidth(), parentContainer->getHeight()));

		GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, textureFormatToOpenGlFormat(parentContainer->getFormat()), parentContainer->getWidth(), parentContainer->getHeight(), 0, textureFormatToOpenGlDataFormat(parentContainer->getFormat()), GL_UNSIGNED_BYTE, NULL));

		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	}

	void openGLTexture::uploadDataFromFile()
	{
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		
        data = stbi_load(parentContainer->getPath().c_str(), parentContainer->getWidthPtr(), parentContainer->getHeightPtr(), parentContainer->getChannelsPtr(), 0);
		
			
		if (data)
		{
			if (parentContainer->getChannels() == 4)
				parentContainer->setFormat(textureFormat::RGBA8);
			else if (parentContainer->getChannels() == 3)
				parentContainer->setFormat(textureFormat::RGB8);
		
			else if (parentContainer->getChannels() == 2)
				parentContainer->setFormat(textureFormat::RG8);


			else if (parentContainer->getChannels() == 1)
				parentContainer->setFormat(textureFormat::R8);

			if (parentContainer->getChannels() == 2) {
				GLint swizzleMask[] = {GL_RED, GL_RED, GL_RED, GL_GREEN};
				glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
            }

			glTextureStorage2D(id, 1, textureFormatToOpenGlFormat(parentContainer->getFormat()), parentContainer->getWidth(), parentContainer->getHeight());

			glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);


			glTextureSubImage2D(id, 0, 0, 0, parentContainer->getWidth(), parentContainer->getHeight(), textureFormatToOpenGlDataFormat(parentContainer->getFormat()), GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}
		else
		{
			LAUGHTALE_ENGINR_LOG_ERROR("failed to load texture frome file:"  << parentContainer->getPath() << "\t because: " << stbi_failure_reason() );
		}
	}

	uint32_t openGLTexture::textureFormatToOpenGlFormat(textureFormat formatToConvert)
	{
		switch (formatToConvert)
		{
			case(textureFormat::None): 				return 0;	break; 

			case(textureFormat::RGBA8): 			return GL_RGBA8;	break; 
			case(textureFormat::RED_INTEGER): 		return GL_R32I;	break; 
			case(textureFormat::RGB8): 				return GL_RGB8;	break; 
			case(textureFormat::RG8): 				return GL_RG8;	break; 
			case(textureFormat::R8): 				return GL_R8;	break; 

			case(textureFormat::DEPTH24STENCIL8): 	return GL_DEPTH24_STENCIL8;	break; 
		}

		return 0;
	}


	uint32_t openGLTexture::textureFormatToOpenGlDataFormat(textureFormat formatToConvert)
	{
		switch (formatToConvert)
		{
			case(textureFormat::None): 				return 0;	break; 

			case(textureFormat::RGBA8): 			return GL_RGBA;	break; 
			case(textureFormat::RED_INTEGER): 		return GL_RED_INTEGER;	break; 
			case(textureFormat::RGB8): 				return GL_RGB;	break; 
			case(textureFormat::RG8): 				return GL_RG;	break; 
			case(textureFormat::R8): 				return GL_R;	break; 

			case(textureFormat::DEPTH24STENCIL8): 	return GL_DEPTH24_STENCIL8;	break; 
		}

		return 0;
	}


}