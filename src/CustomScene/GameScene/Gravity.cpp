#include "CustomScene/GameScene/Gravity.h"
#include "engine/GameObject.h"

Gravity::Gravity(GameObject* obj, float gravityScale) : Component("Gravity", obj), m_gravityScale(gravityScale)
{
	m_rb = static_cast<Rigidbody*>(gameObject->GetComponent("Rigidbody"));
}

Gravity::~Gravity()
{

}

void Gravity::OnIterate()
{
}

void Gravity::OnFixedIterate()
{
	m_rb->AddForce({0, m_gravityScale, 0});
}

std::unique_ptr<Component> Gravity::copy()
{
	return std::make_unique<Gravity>(gameObject, m_gravityScale);
}
