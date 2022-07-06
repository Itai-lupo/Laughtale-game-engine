#pragma once
#include "renderApi.hpp"
#include "vertexArray.hpp"
#include "shader.hpp"
#include "coreCamera.hpp"
#include "mesh.hpp"
#include "scene.hpp"
#include "shaderRenderBuffer.hpp"

#include "coreRenderer.hpp"

#include <map>
#include <set>

namespace LTE
{
    class batchRenderer: public coreRenderer
    {
        private:

            scene *Scene;

            indexBuffer *indicesToRender;
            std::set<shaderRenderBuffer*> shadersToRender;
            std::map<textureId, int> texturesToUse;
            uint8_t textureCounter = 0;
            std::vector<std::pair<textureId, int>> textureSlots;
            std::map<textureId, texture *> textures;
            glm::mat4 ViewProjectionMatrix;
            std::vector<std::shared_ptr<gameObject>> gameObjectsCash;

            void sortSceneToRender();
            void batchSceneData();
            void batchRenderScene();

            shaderRenderBuffer *submitShape(std::shared_ptr<gameObject> shapeObject);

        public:                
            batchRenderer(scene *Scene): Scene(Scene){}


            void renderScene(uint32_t width, uint32_t  hight);
    };
    
    
}
