#pragma once
#include <functional>
#include <vector>
#include <algorithm>
#include <glm/glm.hpp>
#include <functional>

#include "core.h"
#include "logger.h"
#include "component.h"
#include "transform.h"
#include "LTEError.h"

namespace LTE
{
    class gameObjectBuilder;
    class gameObject
    {     
        private:
            gameObjectId id;
            std::string name = "";
            transform *ObjectTransform;
            sceneId parentScene;

            std::vector<component*> components;
            gameObject(sceneId parentScene):parentScene(parentScene){}

        public:    
            friend class gameObjectBuilder;

            const std::string& getName(){ return name; }
            const gameObjectId getId(){ return id; }
            
            template<typename T> 
            T *getComponent()
            {
                if(id == 0 || !ObjectTransform)
                    throw new ComponentNotFoundException("entitys with id 0 have no data ");

                for (auto comp: components)
                {
                    if(comp && dynamic_cast<T*>(comp))
                        return dynamic_cast<T*>(comp); 
                }
                throw new ComponentNotFoundException("can't find Component of type: " + std::string(typeid(T).name()));
                return NULL;
            }    

            template<typename T> 
            void setComponent(component *componentToAdd)
            {
                if(id == 0 || !ObjectTransform)
                    throw new ComponentNotFoundException("entitys with id 0 have no data ");

                for (auto comp: components)
                {
                    if(comp && dynamic_cast<T*>(comp))
                    {
                        comp = componentToAdd; 
                        return;    
                    }
                }

                components.push_back(componentToAdd);
            }    

            template<typename T> 
            void removeComponent()
            {
                if(id == 0 || !ObjectTransform)
                    throw new ComponentNotFoundException("entitys with id 0 have no data ");
                std::vector<component*>::iterator it = std::remove_if(
                        components.begin(), 
                        components.end(),
                        [](component *comp) -> bool
                        {
                            return comp && dynamic_cast<T*>(comp);
                        });

                if(it != components.end())
                    components.erase(it);
            }    

            void end()
            {
                for(auto c: components)
                {
                    c->end();
                    // delete c;
                }
                // components.clear();
                ObjectTransform->end();
                // delete ObjectTransform;
            }

            transform *getTransform()
            {
                return ObjectTransform;
            }

            virtual ~gameObject()
            {
                id = 0;
            }            
    };

    class gameObjectBuilder
    {
        protected:
            gameObject *prodect;
        
        public:
            gameObjectBuilder()
            {
                
            }

            gameObjectBuilder *setObjectName(const std::string& name)
            {
                prodect->name = name;
                return this;
            }

            gameObjectBuilder *setObjectTransform(glm::mat3 trans)
            {
                prodect->ObjectTransform = new transform(trans);
                return this;
            }

            gameObjectBuilder *addComponent(component* toAdd)
            {
                prodect->components.push_back(toAdd);
                return this;
            }     

            gameObjectBuilder *reset(sceneId parentScene)
            {
                prodect = new gameObject(parentScene);
                return this;
            }


            gameObject *build(gameObjectId id)
            {
                for(component *c: prodect->components){
                    c->setParent(id, prodect->parentScene);
                    c->init(prodect);
                }
                prodect->id = id;
                return prodect;
            }

    };
    
    

    class gameObjectsManger
    {
        private:
            gameObjectBuilder *builder;
            std::vector<gameObject*> gameObjects;
            gameObjectId nextGameObjectId = 1;
        public:
            gameObjectsManger();
            ~gameObjectsManger();

            gameObjectId addGameObject(std::function<void(gameObjectBuilder *Builder)> buildGameObject, sceneId parentScene);
            gameObject *getGameObjectByName(const std::string& name);
            gameObject *getGameObjectById(gameObjectId id);
            void removeGameObjectById(gameObjectId id);

    };


}