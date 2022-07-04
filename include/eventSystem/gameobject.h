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
            std::shared_ptr<transform> ObjectTransform;
            sceneId parentScene;
            std::vector<std::shared_ptr<component>> components;

        public:    
            std::weak_ptr<gameObject> self;
            gameObject(sceneId parentScene):parentScene(parentScene){}
            friend class gameObjectBuilder;

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

            template<typename T> 
            void setComponent(std::shared_ptr<component> componentToAdd)
            {
                if(id == 0)
                    throw new ComponentNotFoundException("entitys with id 0 have no data ");

                componentToAdd->setParent(id, parentScene);
                componentToAdd->init(self.lock());
                components.push_back(componentToAdd);
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

            void end()
            {
                for(auto c: components)
                {
                    c->end();
                    c.reset();
                }
                components.clear();
                ObjectTransform->end();
                ObjectTransform.reset();
            }

            transform *getTransform()
            {
                return ObjectTransform.get();
            }

            std::shared_ptr<transform> getTransformPtr()
            {
                return ObjectTransform;
            }

            void forEachComponent(std::function<void(std::shared_ptr<component>)> callback)
            {
                callback(ObjectTransform);
                for (uint64_t i = 0; i < components.size(); i++)
                {
                    callback(components[i]);
                }
            }

            virtual ~gameObject()
            {
                id = 0;
            }            
    };

    class gameObjectBuilder
    {
        protected:
            std::shared_ptr<gameObject> prodect;
        
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
                prodect->ObjectTransform = std::make_shared<transform>(trans);
                return this;
            }

            
            gameObjectBuilder *addComponent(component *toAdd)
            {
                prodect->components.push_back(std::shared_ptr<component>(toAdd));
                return this;
            }     

            gameObjectBuilder *reset(sceneId parentScene)
            {
                prodect = std::make_shared<gameObject>(parentScene);
                return this;
            }


            std::shared_ptr<gameObject> build(gameObjectId id)
            {
                prodect->self = prodect;
                if(!prodect->ObjectTransform)
                    prodect->ObjectTransform = std::make_shared<transform>(glm::mat3());

                prodect->id = id;
                for(std::shared_ptr<component> c: prodect->components){
                    c->setParent(id, prodect->parentScene);
                    c->init(prodect);
                }
                return prodect;
            }

    };
    
    

    class gameObjectsManger
    {
        private:
            gameObjectBuilder *builder;
            std::vector<std::shared_ptr< LTE::gameObject>> gameObjects;
            gameObjectId nextGameObjectId = 1;

        public:
            gameObjectsManger();
            ~gameObjectsManger();

            gameObjectId addGameObject(std::function<void(gameObjectBuilder *Builder)> buildGameObject, sceneId parentScene);
            std::shared_ptr< LTE::gameObject>getGameObjectByName(const std::string& name);
            std::shared_ptr< LTE::gameObject>getGameObjectById(gameObjectId id);
            void removeGameObjectById(gameObjectId id);
            void forEachObject(std::function<void(std::shared_ptr<gameObject>)> callback);

    };


}