#include "CustomScene/GameScene/PlayerArm.h"
#include "engine/GameObject.h"

PlayerArm::PlayerArm(GameObject* obj, GameObject* player) : Component("PlayerArm", obj), m_player(obj)
{
	m_tfs = gameObject->GetTransform();
	m_playerTfs = player->GetTransform();
}

PlayerArm::~PlayerArm()
{

}

void PlayerArm::OnIterate()
{
	//std::cout << "Playerarm moving to: " << m_playerTfs->GetPosition() << std::endl;
	m_tfs->SetPosition(m_playerTfs->GetPosition());
}

std::unique_ptr<Component> PlayerArm::copy()
{
	return std::make_unique<PlayerArm>(gameObject, m_player);
}
