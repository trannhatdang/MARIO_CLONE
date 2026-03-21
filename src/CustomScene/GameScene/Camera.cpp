#include "CustomScene/GameScene/Camera.h"
#include "engine/GameObject.h"

Camera::Camera(GameObject* obj, GameObject* player, void (*setCameraPosFunc)(Vector3)) : Component("Camera", obj), m_player(player), m_setCameraPosFunc(setCameraPosFunc)
{
	m_player_tfs = player->GetTransform();
}

Camera::~Camera()
{

}

void Camera::moveLeft()
{
	Vector3 camPos = GetCameraPos();
	(*m_setCameraPosFunc)(camPos + Vector3(-1, 0, 0));
}

void Camera::moveRight()
{
	Vector3 camPos = GetCameraPos();
	(*m_setCameraPosFunc)(camPos + Vector3(1, 0, 0));
}

void Camera::OnIterate()
{
	Vector3 camPos = GetCameraPos();
	Vector3 playerPos = m_player_tfs->GetPosition();
	SDL_Rect l_rect = { camPos.x, camPos.y, 100, 630 };
	SDL_Rect r_rect = { camPos.x + 315, camPos.y, 560, 630 };

	if(IsPointInsideRect(playerPos, l_rect))
	{
		moveLeft();
	}
	
	if(IsPointInsideRect(playerPos, r_rect))
	{
		moveRight();
	}
}

std::unique_ptr<Component> Camera::copy()
{
	return std::make_unique<Camera>(gameObject, m_player, m_setCameraPosFunc);
}
