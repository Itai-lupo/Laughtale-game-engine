#include <string>

#include "core.h"
#include "window.h"
#include "app.h"
#include "openGL/openGLContext.h"
#include "windowBuilder.h"

#include "orthographicCameraControler.h"

namespace LTE
{
    void windowBuilder::reset()
    {
        product = new window();
    }
    
    window *windowBuilder::build()
    {
        product->id = app::getOSAbstractFactory()->createWindow(product);

        product->context = new openGLContext(product->id);

        if(!product->activeScene){
            product->activeScene = new scene();
            product->activeScene->assetLibrary = new assetManager(product->id);
        }
        
        entityTaleId camId = entityManger::addEntity([=, this](gameObject::gameObjectBuilder *builder){
            builder->setObjectName("default camera")->
                setWindowId(product->id)->
                setObjectTransform(glm::mat4(0.0f))->
                addComponent(new orthographicCameraControler((float)product->Width/(float)product->Height));
        });

        product->activeScene->camera = entityManger::getEntityById(camId);
        
        return product;
    }

    windowBuilder *windowBuilder::setTitle(const std::string& title)
    {
        product->Title = title;
        return this;
    }

    windowBuilder *windowBuilder::setWidth(int width)
    {
        product->Width = width;
        return this;
    }

    windowBuilder *windowBuilder::setHeight(int height)
    {
        product->Height = height;
        return this;
    }

    windowBuilder *windowBuilder::useImGui()
    {
        product->useImGui = true;
        return this;
    }

    windowBuilder *windowBuilder::setActiveScene(scene *activeScene)
    {
        product->activeScene = activeScene;
        return this;
    }
}