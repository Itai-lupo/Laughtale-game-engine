#pragma once
#include "entity.h"
#include "core.h"
#include "shader.h"
#include "VertexBuffer.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace LaughTaleEngine
{
    class VertexBuffer;

    class mesh: public IEntity
    {
    private:
        windowPieceId windowId;

        vertexBufferId VBId;
        indexBufferId IBId;
        vertexArrayId VAId;
        shaderId      ShaderId;

        glm::mat4     transform;
        glm::vec4     material;
    
    public:
        bool isActive = false;
        eventLaughId onRenderId;

        mesh(windowPieceId windowId);

        void setShader(const char *path);
        void setShader(shaderId id);

        void setVertexBuffer(float *vertexs, uint32_t size);
        void setVertexBuffer(vertexBufferId id);

        void setIndexBuffer(uint32_t *indices, uint32_t count);
        void setIndexBuffer(indexBufferId id);

        void setVertexArray();
        void setVertexArray(vertexArrayId id);

        void bind();

        glm::mat4 getTransform(){ return transform; }
        glm::vec4  getmaterial(){ return material; }

        void setTransform(glm::mat4 transform);
        void setmaterial(glm::vec4 material);

        VertexBuffer *getVertexBuffer();
        shader *getShader();
        uint32_t getCount();
        windowPieceId getWindowId() { return windowId; }
    };

}