#include "CustomScene/GameScene/Rocket.h"
#include "engine/GameObject.h"

Rocket::Rocket(GameObject* obj) : Component("Rocket", obj)
{
	m_tfs = gameObject->GetTransform();
}

Rocket::~Rocket()
{

}

void Rocket::OnIterate()
{
	auto pos = m_tfs->GetPosition();

	if(pos.x < 0)
	{
		gameObject->SetActive(false);
	}

	m_tfs->SetPosition(pos + Vector3(-1, 0, 0));
}

std::unique_ptr<Component> Rocket::copy()
{
	return std::make_unique<Rocket>(gameObject);
}
