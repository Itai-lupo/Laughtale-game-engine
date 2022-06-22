#pragma once
#include "simpleQuadRenderer.h"
#include "meshAbsrtactFactory.h"
#include "shaderTypes.h"
#include "windowManger.h"
#include "app.h"

namespace LTE
{

    simpleQuadRenderer::simpleQuadRenderer(const std::string& textureName, scene *Scene, renderApi *renderPipLine): coreRenderer(Scene, renderPipLine), textureName(textureName)
    {
        meshAbsrtactFactory *meshFac = windowManger::getWindow(app::getOsAPI()->getCurrentContextWindowId())->context->getMeshFactory();
        vertexBuffer = meshFac->createVertexBuffer(squrePostions, 4 * 5* sizeof(float));
        indicesToRender = meshFac->createIndexBuffer(squreIndices, 6); 

        vertexBuffer->pushElement({LT_FLOAT, 3, false, 4});
        vertexBuffer->pushElement({LT_FLOAT, 2, false, 4});
        vertexArray = meshFac->createVertexArray(vertexBuffer);
        s = Scene->assetLibrary->getAsset<shaderRenderBuffer>("res/shaders/Basic.glsl")->getShader();
    

    }
    void simpleQuadRenderer::renderScene()
    {
        
        renderPipLine->SetClearColor(Scene->backgroundColor->getRGBA());
        renderPipLine->Clear();
        s->bind();
        s->setUniform1i("textureData", 1);
        s->setUniform4f("MatColor", 0.0f, 0.0f, 0.0f, 0.0f);

        texture *textureData = Scene->assetLibrary->getAsset<texture>(textureName);
        indicesToRender->bind();
        vertexBuffer->bind();
        vertexArray->bind();
        if(textureData)
            textureData->bind(1);

        renderPipLine->DrawIndexed(indicesToRender->getCount());    

    }
    
    
}
