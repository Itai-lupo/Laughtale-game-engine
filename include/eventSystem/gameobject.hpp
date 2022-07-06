#pragma once
#include <functional>
#include <vector>
#include <algorithm>
#include <glm/glm.hpp>
#include <functional>

#include "core.hpp"
#include "logger.hpp"
#include "component.hpp"
#include "transform.hpp"
#include "LTEError.hpp"
namespace LTE
{
    class gameObject
    {     
        private:
            gameObjectId id;
            std::string name = "";
            std::shared_ptr<transform> objectTransform;
            std::vector<std::shared_ptr<component>> components;

        public:    
            gameObject(gameObjectId id, const std::string& name): name(name), id(id), objectTransform(std::make_shared<transform>()){}

            const std::string& getName(){ return name; }
            void setName(const std::string& name){ this->name = name; }
            const gameObjectId getId(){ return id; }
            
            template<typename T> 
            std::shared_ptr<T> getComponent()
            {
                if(id == 0)
                    throw new ComponentNotFoundException("entitys with id 0 have no data ");

                for (auto comp: components)
                {
                    if(comp && dynamic_pointer_cast<T>(comp))
                        return dynamic_pointer_cast<T>(comp); 
                }
                throw new ComponentNotFoundException("can't find Component of type: " + std::string(typeid(T).name()));
                return NULL;
            }    

            template<typename T> 
            bool hasComponent()
            {
                if(id == 0)
                    throw new ComponentNotFoundException("entitys with id 0 have no data ");
                
                for (auto comp: components)
                {
                    if(comp && dynamic_pointer_cast<T>(comp))
                        return true; 
                }

                return false;
            }   

            template<typename T, typename... args> 
            void addComponent(args&&... a)
            {
                if(id == 0)
                    throw new ComponentNotFoundException("entitys with id 0 have no data ");

                std::shared_ptr<component> toAdd = std::make_shared<T>(a...);
                components.push_back(toAdd);
            }    

            template<typename T> 
            void removeComponent()
            {
                if(id == 0)
                    throw new ComponentNotFoundException("entitys with id 0 have no data ");
                auto it = std::remove_if(
                        components.begin(), 
                        components.end(),
                        [](component *comp) -> bool
                        {
                            return comp && dynamic_pointer_cast<T>(comp);
                        });

                if(it != components.end())
                    components.erase(it);
            }    

            ~gameObject()
            {
                for(auto c: components)
                {
                    c.reset();
                }
                components.clear();
                id = 0;
            }


            std::shared_ptr<transform> getTransform()
            {
                return objectTransform;
            }

            void forEachComponent(std::function<void(std::shared_ptr<component>)> callback)
            {
                callback(objectTransform);
                for (uint64_t i = 0; i < components.size(); i++)
                {
                    callback(components[i]);
                }
            }      
    };

    class gameObjectsManger
    {
        private:
            std::vector<std::shared_ptr<gameObject>> gameObjects;
            gameObjectId nextGameObjectId = 1;

        public:
            gameObjectsManger(){}
            ~gameObjectsManger();

            std::shared_ptr<gameObject> addGameObject(const std::string& name);
            void removeGameObjectById(gameObjectId id);
            
            std::shared_ptr<gameObject> getGameObjectByName(const std::string& name);
            std::shared_ptr<gameObject> getGameObjectById(gameObjectId id);

            
            void forEachObject(std::function<void(std::shared_ptr<gameObject>)> callback);

            template<typename t>
            std::vector<std::shared_ptr<gameObject>> getGameObjectCacheByComponentType()
            {
                std::vector<std::shared_ptr<gameObject>> cache;
                forEachObject([&](std::shared_ptr<gameObject> temp)
                {
                    if(temp->hasComponent<t>())
                        cache.push_back(temp);
                });
                return cache;
            }

    };


}