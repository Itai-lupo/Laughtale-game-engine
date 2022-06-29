#pragma once

#include "scene.h"
#include "core.h"
#include "material.h"
#include "orthographicCameraControler.h"

#include <string>
#include <vector>
#include <functional>

namespace LTE
{
    class sceneBuilder
    {
        private:
            scene *product;
        
        public:
            void reset()
            {
                product = new scene();
            }

            scene *build(sceneId id)
            {
                gameObjectId camId = product->addGameObject([=, this](gameObjectBuilder *builder){
                    builder->setObjectName("default camera")->
                        setObjectTransform(glm::mat4(0.0f))->
                        addComponent(new orthographicCameraControler(1280.0f/720.0f));
                });

                product->camera = product->getGameObjectById(camId);
                return product;
        
            }

            void setBackgroundColor(material *color)
            {
                product->backgroundColor = color;
            }

            void setCamera(gameObject *camera)
            {

            }
    };
    
    
    class sceneManger
    {
        private:
            static inline std::vector<scene*> scenes;
            static inline sceneId nextId = 1;
            static inline sceneBuilder* builder;

        public:            
            static void init();
            static void close();

            static sceneId addScene(std::function<void(sceneBuilder *Builder)> buildScene);
            static sceneId removeScene(sceneId sceneID);
                    
            static scene *getScene(sceneId sceneID);
    };
}
    