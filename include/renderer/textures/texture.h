#pragma once
#include <string>
#include "core.h"
#include "asset.h"
#include "logger.h"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace LTE
{
	enum class textureFormat
	{
		None = 0,

		// Color
		RGBA8,
		RED_INTEGER,
        RGB8,
        RG8,
        R8,

		// Depth/stencil
		DEPTH24STENCIL8,

		// Defaults
		Depth = DEPTH24STENCIL8
	};

    struct spriteDimensionsData
    {
        glm::vec2 start;
        glm::vec2 size;

        spriteDimensionsData(glm::vec2 start, glm::vec2 size)
            :start(start), size(size)
        {}
    };

    class texture : public asset
    {
        protected:
            std::string path;
            textureId id;
            int channels;

            bool isSpriteSheet = false;
            bool isCustumSpriteSheet = false;
            glm::vec2 spriteDimensions;
            std::vector<spriteDimensionsData> custumSpriteDimensions;
            
            int width, height;
            textureFormat format;

        public:
            texture(const std::string& path): path(path){}
            virtual ~texture() = default;

            virtual void bind(int slot) = 0;
            textureId getId(){ return id; }
            textureFormat getFormat(){ return format; }

            int getWidth(){return width;}
            int getHeight(){return height;}

            virtual void setDimensions(const glm::vec2 dimensions) = 0;

            bool useSpriteSheet()
            {
                return isSpriteSheet;
            }
            
            bool useCustemSpriteSheet()
            {
                return isCustumSpriteSheet;
            }

            void setSprtieData(const glm::vec2& spriteDimensions)
            {
                this->spriteDimensions = spriteDimensions;
                isSpriteSheet = true;
            }

            void setSprtieData(const std::vector<spriteDimensionsData> spriteDimensions)
            {
                this->custumSpriteDimensions = spriteDimensions;
                isSpriteSheet = true;
                isCustumSpriteSheet = true;
            }

            float getSpriteX(int spriteXId)
            {
                return spriteXId * (spriteDimensions.x / (float)width);
            }


            float getSpriteY(int spriteYId)
            {
                return spriteYId * (spriteDimensions.y / (float)height);
            }

            glm::vec2 getSpirteStartById(int spriteId)
            {
                return custumSpriteDimensions[spriteId].start / glm::vec2((float)width, (float)height);
            }

            glm::vec2 getSpirteSizeById(int spriteId)
            {
                return custumSpriteDimensions[spriteId].size / glm::vec2((float)width, (float)height);
            }

            float getSpriteYDelte()
            {
                return spriteDimensions.y / (float)height;
            }

            float getSpriteXDelte()
            {
                return spriteDimensions.x / (float)width;
            }
    };
}