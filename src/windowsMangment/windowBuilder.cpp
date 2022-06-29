#include <string>

#include "core.h"
#include "window.h"
#include "app.h"
#include "graphicsContext.h"
#include "windowBuilder.h"


namespace LTE
{
    void windowBuilder::reset()
    {
        product = new window();
    }
    
    window *windowBuilder::build()
    {
        product->id = app::getOSAbstractFactory()->createWindow(product);

        product->context = new graphicsContext(product, OpenGL);      
        
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
}