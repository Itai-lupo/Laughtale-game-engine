#pragma once
#include <string>
#include <boost/thread.hpp>

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

    class texture;
    class textureRenderApi
    {
        protected:
            texture *parentContainer;
            
            std::atomic<int> changeId = 0;

        public:
            textureRenderApi(texture *parentContainer): parentContainer(parentContainer){}
            virtual ~textureRenderApi() = default;

            virtual void bind(int slot) = 0;
            virtual textureId getId() = 0;
        	virtual void setDimensions() = 0;
            

    };

    class texture: public asset
    {
        private:
            std::string path;
            int channels = 4;
            int samples = 1;

            bool isSpriteSheet = false;
            bool isCustumSpriteSheet = false;
            glm::vec2 spriteDimensions;
            std::vector<spriteDimensionsData> custumSpriteDimensions;
            
            int width, height;
            textureFormat format = textureFormat::RGBA8;

            boost::thread_specific_ptr<textureRenderApi> data;
            std::atomic<int> changeId = 0;

            void checkIfExitesInThisContextAndInitIfNot();
        public:
            texture(const std::string& path): path(path)
            {

            }
            
            void bind(int slot)
            {
                checkIfExitesInThisContextAndInitIfNot();
                data->bind(slot);
            }

            virtual void setDimensions(const glm::vec2 dimensions)
            {
                checkIfExitesInThisContextAndInitIfNot();
                if(width == dimensions.x && height == dimensions.y)
                    return;
                width = dimensions.x;
                height = dimensions.y;
                
                changeId++;
                data->setDimensions();
            }

            virtual textureId getId()
            {
                checkIfExitesInThisContextAndInitIfNot();

                return data->getId();
            }

            textureFormat getFormat()
            {
                return format; 
            }

            int getWidth()
            {
                return width;
            }

            int getHeight()
            {
                return height;
            }

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


            std::string getPath()
            {
                return path;
            }

            int getChannels()
            {
                return channels;
            }

            int getSamples()
            {
                return samples;
            }

            void setSamples(int samples)
            {
                this->samples = samples;
                changeId++;
            }

            int *getWidthPtr()
            {
                return &width;
            }

            int *getHeightPtr()
            {
                return &height;
            }

            int *getChannelsPtr()
            {
                return &channels;
            }

            unsigned int getChangeId()
            {
                return changeId;
            }

            void setFormat(textureFormat f)
            {
                format = f;
            }
    };
}