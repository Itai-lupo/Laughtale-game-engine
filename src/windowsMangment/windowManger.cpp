#include "windowManger.h"
#include "logger.h"
#include <string>
#include <functional>
#include <algorithm>
#include "LTEError.h"
#include "app.h"

namespace LTE
{
    windowManger::windowManger(): osEvent({osEventsType::WindowClose})
    {
        buildWindow = new windowBuilder();
    }
    
    windowManger::~windowManger()
    {
        for (window* win: windows)
        {
            delete win;
        }
        
        delete buildWindow;
    }    

    void windowManger::onWindowClose(osEventData *sendor)
    {        
        window *toDelete = getWindow(sendor->windowId);
        windows.erase(std::remove_if(
            windows.begin(), 
            windows.end(), 
            [=](window *win)-> bool { return win->id == sendor->windowId; }
        ), windows.end());

        delete toDelete;
    }


    windowPieceId windowManger::addWindow(std::function<void(windowBuilder *Builder)> build)
    {
        buildWindow->reset();
        build(buildWindow);
        
        window *newWindow = buildWindow->build();

        windows.push_back(newWindow);
        newWindow->init();        
        return newWindow->id;
    }

    window *windowManger::getWindow(windowPieceId windowId)
    {
        auto temp = std::find_if(                                                       
                windows.begin(),                                            
                windows.end(),                                              
                [=](window *win)-> bool { return win->id == windowId; }     
            );

        if(temp != windows.end())
            return *temp;
        
        throw new WindowNotFoundException("window " + std::to_string(windowId) + " wasn't found");
        return NULL;
    }

}