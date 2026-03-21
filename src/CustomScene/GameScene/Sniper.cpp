#include "CustomScene/GameScene/Sniper.h"

Sniper::Sniper(GameObject* obj, Scene* currScene) : Component("Sniper", obj), m_scene(currScene)
{

}

Sniper::~Sniper()
{

}

void Sniper::OnIterate()
{

}

std::unique_ptr<Component> Sniper::copy()
{
	return std::make_unique<Sniper>(gameObject, m_scene);
}

bool Sniper::IsShooting() const
{
	return m_shooting;
}
