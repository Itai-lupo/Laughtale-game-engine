#include "app.hpp"
#include "orthographicCameraControler.hpp"
#include "logger.hpp"
#include "MouseButtonCodes.hpp"

#include "window.hpp"
#include "windowManger.hpp"

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
        }
        mouseLastPostion = win->inputManger->GetMousePosition();
    }

    orthographicCameraControler::orthographicCameraControler(float aspectRatio, bool useCameraRotation)
        :   osEvent({ osEventsType::windowRender, osEventsType::WindowResize, osEventsType::MouseScroll }), 
            aspectRatio(aspectRatio), camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel), 
            useCameraRotation(useCameraRotation)
    {

    }
    void orthographicCameraControler::setAspectRatio(float aspectRatio)
    {
        if(this->aspectRatio == aspectRatio)
            return;
        this->aspectRatio = aspectRatio;
        camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
    }

    orthographicCameraControler::~orthographicCameraControler()
    {

    }
    
    coreCamera *orthographicCameraControler::getCamera()
    {
        return &camera;
    }
}