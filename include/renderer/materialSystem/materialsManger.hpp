#pragma once
#include "core.hpp"
#include "shader.hpp"
#include <vector>

namespace LTE
{
    class material;
    class materialsManger
    {
        private:
            static std::vector<material *> *materials;
            static materialId nextId;
        public:
            static void init();
            static void close();

            static materialId addMatrial(material *toAdd);
            static void bind(materialId id, shader *shaderToBindTo, std::vector<uint32_t> textureSlots = {});
            static material *getMaterial(materialId id);
    };
    

}