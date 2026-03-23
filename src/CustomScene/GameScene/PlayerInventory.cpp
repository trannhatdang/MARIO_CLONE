#include "CustomScene/GameScene/PlayerInventory.h"
#include "engine/GameObject.h"

PlayerInventory::PlayerInventory(GameObject* obj, Font* font) : Component("PlayerInventory", obj), m_font(font)
{

}

PlayerInventory::~PlayerInventory()
{

}

void PlayerInventory::OnIterate()
{
	m_font->SetText("Score: " + std::to_string(m_playerPoints) + " Punch: " + (m_hasSuperPunch ? "Super" : "Normal"));
}

std::unique_ptr<Component> PlayerInventory::copy()
{
	return std::make_unique<PlayerInventory>(gameObject, m_font);
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

void PlayerInventory::SetFont(Font* font)
{
	m_font = font;
}
