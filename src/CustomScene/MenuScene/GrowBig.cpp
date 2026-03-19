#include "CustomScene/MenuScene/GrowBig.h"
#include "engine/GameObject.h"

GrowBig::GrowBig(GameObject* obj) : Component("GrowBig", obj)
{
	m_spr = static_cast<SpriteRenderer*>(gameObject->GetComponent("SpriteRenderer"));

}

GrowBig::~GrowBig()
{

}

void GrowBig::OnIterate()
{

}

std::unique_ptr<Component> GrowBig::copy()
{
	return std::make_unique<GrowBig>(gameObject);
}

void GrowBig::TurnOn()
{
	m_isBig = true;
}

void GrowBig::TurnOff()
{
	m_isBig = false;
}
