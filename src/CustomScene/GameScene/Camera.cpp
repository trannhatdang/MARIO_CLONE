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
	Vector3 playerPos = m_player_tfs->GetPosition();
	Player* player = static_cast<Player*>(m_player->GetComponent("Player"));
	SDL_Rect l_rect = { 0, 0, 50, 630 };
	SDL_Rect r_rect = { 720, 0, 400, 630 };

	if(!player->IsRunning())
	{
		return;
	}

	if(IsPointInsideRect(playerPos, l_rect) && player->IsFacingLeft())
	{
		moveLeft();
	}
	
	if(IsPointInsideRect(playerPos, r_rect) && !player->IsFacingLeft())
	{
		moveRight();
	}
}

std::unique_ptr<Component> Camera::copy()
{
	return std::make_unique<Camera>(gameObject, m_player, m_setCameraPosFunc);
}
