#include "sceneManger.h"


namespace LTE
{
    void sceneManger::init()
    {
        builder = new sceneBuilder();
    }

    void sceneManger::close()
    {
        for(scene* s: scenes)
        {
            delete s;
        }
        delete builder;
        scenes.clear();
    }


    sceneId sceneManger::addScene(std::function<void(sceneBuilder *Builder)> buildScene)
    {
        builder->reset();
        buildScene(builder);

        scene *newScene = builder->build(nextId);

        scenes.push_back(newScene);
        
        nextId++;
        return newScene->id;
    }

    sceneId sceneManger::removeScene(sceneId sceneID)
    {
        scene *s = getScene(sceneID);

        scenes.erase(std::remove_if(
            scenes.begin(), 
            scenes.end(), 
            [=](scene* s)-> bool { return s->id == sceneID; }
        ), scenes.end());

        if(s)
            delete s;
    }

            
    scene *sceneManger::getScene(sceneId sceneID)
    {

        auto temp = std::find_if(  
            scenes.begin(), 
            scenes.end(), 
            [=](scene* s)-> bool { return s->id == sceneID; }
        );

        if(temp != scenes.end())
            return *temp;
        
        return NULL;
    }

}