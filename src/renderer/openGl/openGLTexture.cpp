#pragma once
#include "glad/glad.h"

#include "openGLTexture.h"
#include "stb_image.h"
#include "handleOpenGlErrors.h"


namespace LTE
{
    openGLTexture::openGLTexture(const std::string& path): texture(path)
    {
		format = textureFormat::RGBA8;
        
    }

    openGLTexture::~openGLTexture()
    {
        glDeleteTextures(1, &id);
    }

    void openGLTexture::init()
    {

		GL_CALL(glCreateTextures(GL_TEXTURE_2D, 1, &id));
		
		if(path != "")
			uploadDataFromFile();
    }


    void openGLTexture::bind(int slot)
    {
		GL_CALL(glBindTextureUnit(slot, id));
    }
    
    void openGLTexture::unbind()
    {
        GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
    }

	void openGLTexture::setDimensions(const glm::vec2 dimensions)
	{
		if(width == dimensions.x && height == dimensions.y)
			return;
		width = dimensions.x;
		height = dimensions.y;
		
        glDeleteTextures(1, &id);
		GL_CALL(glCreateTextures(GL_TEXTURE_2D, 1, &id));

		GL_CALL(glTextureStorage2D(id, 1, textureFormatToOpenGlFormat(format), width, height));

		GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, textureFormatToOpenGlFormat(format), width, height, 0, textureFormatToOpenGlDataFormat(format), GL_UNSIGNED_BYTE, NULL));

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
		
        data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		
			
		if (data)
		{
			if (channels == 4)
				format = textureFormat::RGBA8;
			else if (channels == 3)
				format = textureFormat::RGB8;
		
			else if (channels == 2)
				format = textureFormat::RG8;


			else if (channels == 1)
				format = textureFormat::R8;

			if (channels == 2) {
				GLint swizzleMask[] = {GL_RED, GL_RED, GL_RED, GL_GREEN};
				glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
            }

			glTextureStorage2D(id, 1, textureFormatToOpenGlFormat(format), width, height);

			glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);


			glTextureSubImage2D(id, 0, 0, 0, width, height, textureFormatToOpenGlDataFormat(format), GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}
		else
		{
			LAUGHTALE_ENGINR_LOG_ERROR("failed to load texture frome file:"  << path << "\t because: " << stbi_failure_reason() );
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