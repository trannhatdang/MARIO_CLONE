#include "CustomScene/GameScene/PlayerPunch.h"
#include "engine/GameObject.h"

PlayerPunch::PlayerPunch(GameObject* obj) : Component("PlayerPunch", obj)
{
	
}

PlayerPunch::~PlayerPunch()
{

}

void PlayerPunch::OnIterate()
{
	m_timeAlive += DGTime_deltaTime();

	if(m_timeAlive > m_aliveTime)
	{
		gameObject->SetActive(false);
	}
}

std::unique_ptr<Component> PlayerPunch::copy()
{
	return std::make_unique<PlayerPunch>(gameObject);
}
