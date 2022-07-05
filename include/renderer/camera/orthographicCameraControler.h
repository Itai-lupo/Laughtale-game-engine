#pragma once
#include "core.h"
#include "coreCameraControler.h"
#include "orthographicCamera.h"
#include "gameobject.h"
#include "osEvents.h"

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
    
            virtual float getAspectRatio() { return  aspectRatio; }

            virtual coreCamera *getCamera() override;


    };
}