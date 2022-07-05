#include "sceneManger.h"


namespace LTE
{
    void sceneManger::init()
    {

    }

    void sceneManger::close()
    {
        for(scene* s: scenes)
        {
            delete s;
        }
        scenes.clear();
    }


    scene *sceneManger::addScene(const std::string& title)
    {        
        scene *newScene = new scene(nextId);
        newScene->camera = newScene->addGameObject("default camera");
        newScene->camera->addComponent<orthographicCameraControler>(1280.0f/720.0f);

        scenes.push_back(newScene);
        
        nextId++;
        return newScene;
    }

    void sceneManger::removeScene(sceneId sceneID)
    {
        scene *s = getScene(sceneID);

        scenes.erase(std::remove_if(
            scenes.begin(), 
            scenes.end(), 
            [=](scene* s)-> bool { return s->getId() == sceneID; }
        ), scenes.end());

        if(s)
            delete s;
    }
            
    scene *sceneManger::getScene(sceneId sceneID)
    {

        auto temp = std::find_if(  
            scenes.begin(), 
            scenes.end(), 
            [=](scene* s)-> bool { return s->getId() == sceneID; }
        );

        if(temp != scenes.end())
            return *temp;
        
        return NULL;
    }

}