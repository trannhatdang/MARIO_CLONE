#include "CustomScene/GameScene/PlayerBullet.h"
#include "engine/GameObject.h"

PlayerBullet::PlayerBullet(GameObject* obj, Vector3 dir, float delay) : Component("PlayerBullet", obj), m_dir(dir), m_delay(delay)
{
	m_tfs = gameObject->GetTransform();
	m_timeSinceLastMovement = 0.0f;
}

PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::OnIterate()
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

void PlayerBullet::OnCollisionEnter(GameObject* other)
{
	if(other->GetTag() == "Sniper")
	{
		gameObject->SetActive(false);
	}
}

std::unique_ptr<Component> PlayerBullet::copy()
{
	return std::make_unique<PlayerBullet>(gameObject, m_dir, m_delay);
}
