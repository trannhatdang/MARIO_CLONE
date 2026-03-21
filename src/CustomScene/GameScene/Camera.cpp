#include "CustomScene/GameScene/Camera.h"

Camera::Camera(GameObject* obj, GameObject* player, void (*setCameraPosFunc)(Vector3)) : Component("Camera", obj), m_player(player), m_setCameraPosFunc(setCameraPosFunc)
{

}

Camera::~Camera()
{

}

void Camera::OnIterate()
{
	Vector3 camPos = GetCameraPos();
	SDL_Rect l_rect = { camPos.x, camPos.y, 100, 630 };
	SDL_Rect r_rect = { camPos.x + 315, camPos.y, 560, 630 };

}

std::unique_ptr<Component> Camera::copy()
{
	return std::make_unique<Camera>(gameObject, m_player, m_setCameraPosFunc);
}
