#include "app.h"
#include "orthographicCameraControler.h"
#include "logger.h"
#include "MouseButtonCodes.h"

#include "window.h"
#include "windowManger.h"

namespace LTE
{
    void orthographicCameraControler::onMouseScroll(mouseScrollData *sendor)
    {
        zoomLevel -= sendor->yOffset * 0.25f;
		zoomLevel = std::max(zoomLevel, 0.25f);

		camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
    }

    void orthographicCameraControler::onWindowResize(WindowResizeData *sendor)
    {
        aspectRatio = (float)sendor->windowWidth / (float)sendor->windowHeight;
		camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
    }

    void orthographicCameraControler::onWindowRender(windowRenderData *sendor)
    {
        window *win = app::getWindowManger()->getWindow(sendor->windowId);

        if(win->inputManger->isMouseButtonPressed(LT_MOUSE_BUTTON_MIDDLE))
        {
            glm::vec3 cameraPostion = camera.getPosition();
            cameraPostion.x += ((win->inputManger->GetMouseX() - mouseLastPostion.x) * (1 /  (float)win->Width)) * sendor->DeltaTime;
            cameraPostion.y += ((win->inputManger->GetMouseY() - mouseLastPostion.y) * (1 / (float)win->Height)) * sendor->DeltaTime;

            camera.SetPosition(cameraPostion);
            LAUGHTALE_ENGINR_LOG_INFO(win->inputManger->GetMouseX()  << ", " << cameraPostion.y);
        }
        mouseLastPostion = win->inputManger->GetMousePosition();
    }

    orthographicCameraControler::orthographicCameraControler(float aspectRatio, bool useCameraRotation)
        :   osEvent({ osEventsType::windowRender, osEventsType::WindowResize, osEventsType::MouseScroll }), 
            aspectRatio(aspectRatio), camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel), 
            useCameraRotation(useCameraRotation)
    {

    }

    orthographicCameraControler::~orthographicCameraControler()
    {

    }
    
    coreCamera *orthographicCameraControler::getCamera()
    {
        return &camera;
    }
}