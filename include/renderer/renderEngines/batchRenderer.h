#pragma once
#include "renderApi.h"
#include "vertexArray.h"
#include "shader.h"
#include "coreCamera.h"
#include "mesh.h"
#include "scene.h"
#include "shaderRenderBuffer.h"

#include "coreRenderer.h"

#include <map>
#include <set>

namespace LTE
{
    class batchRenderer: public coreRenderer
    {
        private:
            indexBuffer *indicesToRender;
            std::set<shaderRenderBuffer*> shadersToRender;
            std::map<textureId, int> texturesToUse;
            uint8_t textureCounter = 0;
            std::vector<std::pair<textureId, int>> textureSlots;
            std::map<textureId, texture *> textures;
            glm::mat4 ViewProjectionMatrix;

            void sortSceneToRender();
            void batchSceneData();
            void batchRenderScene();


        public:                
            batchRenderer(scene *Scene, renderApi *renderPipLine): coreRenderer(Scene, renderPipLine){}

            shaderRenderBuffer *submitShape(mesh *shape, material *shapeMatrial);

            void renderScene();
    };
    
    
}