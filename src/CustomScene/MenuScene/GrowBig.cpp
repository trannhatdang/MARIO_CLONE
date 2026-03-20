#include "CustomScene/MenuScene/GrowBig.h"
#include "engine/GameObject.h"

GrowBig::GrowBig(GameObject* obj, SDL_FRect onRect, float delay) : Component("GrowBig", obj), m_onRect(onRect), m_delay(delay)
{
	m_spr = static_cast<SpriteRenderer*>(gameObject->GetComponent("SpriteRenderer"));

	if(!m_spr)
	{
		return;
	}
}

GrowBig::~GrowBig()
{

}

void GrowBig::OnIterate()
{
	if(!m_spr)
	{
		return;
	}

	m_timeSinceLastGrowth += DGTime_deltaTime();

	if(m_timeSinceLastGrowth < m_delay)
	{
		return;
	}

	m_timeSinceLastGrowth = 0.0f;

	if(m_isBig && m_currScale < 100)
	{
		m_spr->SetDstRect(MultRect(m_onRect, ++m_currScale / 100.0f));
	}
	else if(!m_isBig && m_currScale > 0)
	{
		m_spr->SetDstRect(MultRect(m_onRect, --m_currScale / 100.0f));
	}
}

std::unique_ptr<Component> GrowBig::copy()
{
	return std::make_unique<GrowBig>(gameObject, m_onRect);
}

void GrowBig::TurnOn(void (*callBackFunc)())
{
	m_isBig = true;
	m_callBackFunc = callBackFunc;
}

void GrowBig::TurnOff(void (*callBackFunc)())
{
	m_isBig = false;
	m_callBackFunc = callBackFunc;
}
