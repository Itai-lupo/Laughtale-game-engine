#include "simpleQuadRenderer.h"
#include "meshAbsrtactFactory.h"
#include "shaderTypes.h"
#include "windowManger.h"
#include "app.h"
#include "assetManager.h"

namespace LTE
{

    simpleQuadRenderer::simpleQuadRenderer(const std::string& textureName): textureName(textureName)
    {
        vertexBufferData = new VertexBuffer(squrePostions, 4 * 5* sizeof(float));
        indicesToRender = new indexBuffer(squreIndices, 6); 

        vertexBufferData->pushElement({LT_FLOAT, 3, false, 4});
        vertexBufferData->pushElement({LT_FLOAT, 2, false, 4});
        vertexArrayData = new vertexArray(vertexBufferData);
        
        s = assetManager::getAsset<shaderRenderBuffer>("res/shaders/Basic.glsl")->getShader();
        

    }

    void simpleQuadRenderer::renderScene(uint32_t width, uint32_t  hight)
    {
        
        graphicsContext::getRenderApi()->SetClearColor({1, 0, 0, 1});
        graphicsContext::getRenderApi()->Clear();
        s->bind();
        s->setUniform1i("textureData", 1);
        s->setUniform4f("MatColor", 0.0f, 0.0f, 0.0f, 0.0f);

        texture *textureData = assetManager::getAsset<texture>(textureName);

        vertexArrayData->bind();
        indicesToRender->bind();

        if(textureData)
            textureData->bind(1);

        graphicsContext::getRenderApi()->DrawIndexed(indicesToRender->getCount());    

    }
    
    
}
