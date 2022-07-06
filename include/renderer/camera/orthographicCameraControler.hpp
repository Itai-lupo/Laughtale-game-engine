#pragma once
#include "core.hpp"
#include "coreCameraControler.hpp"
#include "orthographicCamera.hpp"
#include "gameobject.hpp"
#include "osEvents.hpp"

namespace LTE
{
    class orthographicCameraControler: public coreCameraControler, osEvent
    {
        private:

            float aspectRatio;
            float zoomLevel = 1.0f;
            bool useCameraRotation;

            glm::vec2 mouseLastPostion = {0, 0};

            glm::vec3 cameraPosition = { 0.0f, 0.0f, 0.0f };
            float cameraRotation = 0.0f;
            float cameraTranslationSpeed = 5.0f, cameraRotationSpeed = 180.0f;

            orthographicCamera camera;

            eventLaughId OnMouseScrolledId; 
            eventLaughId OnWindowResizedId; 
            eventLaughId OnUpdateId; 
            gameObjectId CameraEntityId;

            void onMouseScroll(mouseScrollData *sendor);
            void onWindowResize(WindowResizeData *sendor);
            void onWindowRender(windowRenderData *sendor);
        public:
            orthographicCameraControler(float aspectRatio, bool useCameraRotation = false);
            ~orthographicCameraControler();
    
            virtual void setAspectRatio(float aspectRatio) override;
            virtual float getAspectRatio() { return  aspectRatio; }

            virtual coreCamera *getCamera() override;


    };
}