#pragma once
#include "core.hpp"
#include "shader.hpp"
#include "materialsManger.hpp"
#include "texture.hpp"
#include "component.hpp"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

namespace LTE
{
    class material: public component
    {
        private:
            friend materialsManger;
            materialId id;

            texture *tex = nullptr;
            glm::vec4 baseColor;

            std::string texturePath;
            int tileXIndex = 0, tileYIndex = 0;
            int tileIndex = 0;

            std::vector<glm::vec2> texturePostions = {{0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}};

        public:
            material(const std::string& textureFilePath, glm::vec4 baseColor);
            material(const std::string& textureFilePath, int tileXIndex, int tileYIndex);
            material(const std::string& textureFilePath, int tileIndex);
            material(const std::string& textureFilePath);
            material(glm::vec4 baseColor);
            material(material *temp);

            ~material(){
            }

            void bind();
            void bind(std::vector<uint32_t> textureSlots);

            void setTexture(texture *tex);
            void setTexture(const std::string& path);
            void setBaseColor(glm::vec4 baseColor);

            void setTileIndex(int tileXIndex, int tileYIndex);
            void setTileIndex(int tileIndex);
            
            std::string getTextureName();
            texture *getTexture();
            textureId getTextureId();
            glm::vec4 getRGBA();

            float getTexturePostionX(int curnerIndex);
            float getTexturePostionY(int curnerIndex);


            virtual std::string getName() override
            { 
                return "material";
            }

            virtual void displayComponentProprties() override
            {            
    			ImGui::ColorEdit4("Color", glm::value_ptr(baseColor));
            }
    };

    class matrialFactory: public componentAbstractFactory
    {
        public:
            virtual ~matrialFactory() = default;

            virtual std::shared_ptr<component> createComponent() override
            {
                return std::make_shared<material>(glm::vec4{1, 1, 1, 1});
            }
    };
}