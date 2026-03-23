#include "CustomScene/GameScene/SniperBullet.h"
#include "engine/GameObject.h"

SniperBullet::SniperBullet(GameObject* obj, Vector3 dir, float delay) : Component("SniperBullet", obj), m_dir(dir), m_delay(delay)
{
	m_tfs = gameObject->GetTransform();
	m_timeSinceLastMovement = 0.0f;
}

SniperBullet::~SniperBullet()
{

}

void SniperBullet::OnIterate()
{
	Vector3 pos = m_tfs->GetPosition();

	if(pos.x < -10000 || pos.x > 10000)
	{
		gameObject->SetActive(false);
	}

	if(!m_tfs)
	{
		return;
	}

	m_timeSinceLastMovement += DGTime_deltaTime();

	if(m_timeSinceLastMovement < m_delay)
	{
		return;
	}

	m_timeSinceLastMovement = 0.0f;

	m_tfs->SetPosition(pos + m_dir);
}

std::unique_ptr<Component> SniperBullet::copy()
{
	return std::make_unique<SniperBullet>(gameObject, m_dir, m_delay);
}
