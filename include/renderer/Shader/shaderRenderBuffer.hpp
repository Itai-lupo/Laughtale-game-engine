#pragma once
#include <vector>
#include<string>
#include <glm/glm.hpp>

#include "shader.hpp"
#include "indexBuffer.hpp"
#include "vertexArray.hpp"
#include "VertexBuffer.hpp"
#include "mesh.hpp"
#include "material.hpp"

#include <map>
#include <vector>

namespace LTE
{
    struct vertexsData
    {
        float x, y, z;
        float textCoordX, textCoordY;
        float r, g, b, a;
        union
        {
            float textureSlot;
            textureId texId;
        };
        
    };


    class shaderRenderBuffer : public asset
    {        
        private:
            static inline indexBuffer *BatchedIndexBuffer;
            shader *s;
            VertexBuffer *BatchedVertexBuffer;
            vertexArray *BatchedVertexArray;

            std::vector<vertexsData> verticesData;
            std::vector<unsigned int> shapeIndexCounter;
            std::vector<unsigned int> indices;

            int renderBatchEnd = 0;
            int batchIndexCount = 0;

        public:
            shaderRenderBuffer(shader *s);
            shader *getShader();

            void pushShape(std::shared_ptr<gameObject> shapeObject);
            void setTextureIndex(std:: map<textureId, int>& textures);
            void print();

            void bind();
            void unbind();

            int getIndecesCount();
            unsigned int *getIndecesData(){ return indices.data(); }
            bool isAllRendered();
            void clear();
    };
}
