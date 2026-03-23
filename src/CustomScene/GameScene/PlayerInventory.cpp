#include "CustomScene/GameScene/PlayerInventory.h"
#include "engine/GameObject.h"

PlayerInventory::PlayerInventory(GameObject* obj) : Component("PlayerInventory", obj)
{

}

PlayerInventory::~PlayerInventory()
{

}

void PlayerInventory::OnIterate()
{

}

std::unique_ptr<Component> PlayerInventory::copy()
{
	return std::make_unique<PlayerInventory>(gameObject);
}

void PlayerInventory::AddPoints(int val)
{
	m_playerPoints += val;
}

void PlayerInventory::SetPunch()
{
	m_hasSuperPunch = true;
}

int PlayerInventory::GetPlayerPoints() const
{
	return m_playerPoints;
}

bool PlayerInventory::HasSuperPunch() const
{
	return m_hasSuperPunch;
}
