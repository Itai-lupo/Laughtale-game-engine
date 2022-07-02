#include "batchRenderer.h"
#include "mesh.h"
#include "windowManger.h"
#include "shaderTypes.h"
#include "LTEError.h"
#include "app.h"

#include <algorithm>

namespace LTE
{

    shaderRenderBuffer *batchRenderer::submitShape(std::shared_ptr<mesh> shape, std::shared_ptr<material> shapeMatrial)
    {
        shaderRenderBuffer *s  = assetManager::getAsset<shaderRenderBuffer>(shape->getShaderName());
        if(!s)
            return nullptr;
        s->pushShape(shape, shapeMatrial);
        return s;
    }

    void batchRenderer::sortSceneToRender()
    {
        std::sort(
            Scene->objects->begin(),
            Scene->objects->end(),
            [=](std::weak_ptr< LTE::gameObject> a, std::weak_ptr< LTE::gameObject> b) -> bool
            {
                try
                {
                    return a.lock()->getTransform()->getPostion().z < b.lock()->getTransform()->getPostion().z;
                }
                catch(LTEException* e)
                {
                    LAUGHTALE_ENGINR_LOG_ERROR(e->what());
                    return false;
                }
                
            });
    }

    void batchRenderer::batchSceneData()
    {

        for(std::weak_ptr<LTE::gameObject> toRenderWeak: *Scene->objects)
        {
            std::shared_ptr<LTE::gameObject> toRender = toRenderWeak.lock();
            if(!toRender)
                continue;

            try
            {
                std::shared_ptr<mesh> obj = toRender->getComponent<mesh>();
                std::shared_ptr<material> objMat = toRender->getComponent<material>();
                if(!obj || !objMat)
                    continue;
                shaderRenderBuffer *s  = submitShape(obj, objMat);
                if(!s)
                    continue;
                shadersToRender.insert(s);
                if(!textures[objMat->getTextureId()])
                {
                    textures[objMat->getTextureId()] = objMat->getTexture();
                }
            }
            catch(LTEException* e)
            {
                LAUGHTALE_ENGINR_LOG_ERROR("can't render " << e->what());
            }
        }
    }

    void batchRenderer::batchRenderScene()
    {
        for(auto& shaderBuffer: shadersToRender)
        {
            shader *s = shaderBuffer->getShader();
            s->bind();
            int *samplers = (int*)calloc(4, 8);
            for(int *i = samplers; i < samplers + 8; i++)
                *i = ((long)i - (long)samplers)/4;
            
            s->setUniformMat4f("viewProjection", ViewProjectionMatrix);
            s->setUniform1iv("textures", samplers, 8);

            while (!shaderBuffer->isAllRendered())
            {
                try
                {
                    shaderBuffer->setTextureIndex(texturesToUse);
                    for(const auto& [id, slot]: texturesToUse)
                        if(textures[id])
                            textures[id]->bind(slot);
                    shaderBuffer->bind();

                    graphicsContext::getRenderApi()->DrawIndexed(shaderBuffer->getIndecesCount());
                }
                catch(const std::exception& e)
                {
                    LAUGHTALE_ENGINR_LOG_WARNING("could not render game object because: " << e.what());
                }
                catch(...)
                {
                    LAUGHTALE_ENGINR_LOG_WARNING("could not render shader data");
                }

                texturesToUse.clear();
            }
            shaderBuffer->clear();
        }
    }

    void batchRenderer::renderScene()
    {
        ViewProjectionMatrix = Scene->camera->getComponent<coreCameraControler>()->getCamera()->getViewProjectionMatrix();
        
        graphicsContext::getRenderApi()->SetClearColor(Scene->backgroundColor->getRGBA());
        graphicsContext::getRenderApi()->Clear();

        sortSceneToRender();
        batchSceneData();

        batchRenderScene();
        
    }
}  