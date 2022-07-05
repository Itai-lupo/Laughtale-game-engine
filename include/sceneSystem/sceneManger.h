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
    class sceneManger
    {
        private:
            static inline std::vector<scene*> scenes;
            static inline sceneId nextId = 1;

        public:            
            static void init();
            static void close();

            static scene *addScene(const std::string& title = "untitled");
            static void removeScene(sceneId sceneID);
                    
            static scene *getScene(sceneId sceneID);
    };
}
    