#include "CustomScene/GameScene/Sniper.h"

Sniper::Sniper(GameObject* obj, Scene* currScene, PlayerInventory* playerInven, Audio* audio) : Component("Sniper", obj), m_scene(currScene), m_audio(audio), m_playerInven(playerInven)
{
}

Sniper::~Sniper()
{

}

void Sniper::shoot()
{
	m_timeSinceLastShot += DGTime_deltaTime();

	if(m_timeSinceLastShot < m_shootDelay)
	{
		return;
	}

	m_timeSinceLastShot = 0.0f;

	auto newBullet = m_scene->AddGameObject("Bullet", "SniperBullet");
	newBullet->GetTransform()->SetPosition(gameObject->GetTransform()->GetPosition());
	newBullet->AddComponent(new SpriteRenderer(newBullet, m_scene->GetRenderer(), GetSniperBulletSprite(), { 0, 0, 0 }, { 0, 0, 100, 100 }, { 0, 0, 25, 25 }));
	newBullet->AddComponent(new SniperBullet(newBullet, {-1, 0, 0} , 0.01f));
	newBullet->AddComponent(new BoxCollider(newBullet, { 25, 25 }, true, true));
}

void Sniper::OnIterate()
{
	if(m_shooting)
	{
		m_timeSinceStartedShooting += DGTime_deltaTime();

		if(m_timeSinceStartedShooting < m_shootingTime)
		{
			shoot();
			return;
		}

		m_timeSinceStartedShooting = 0.0f;
		m_shooting = false;
	}
	else
	{
		m_shooting = (rand() % 200 < 5);
	}

	if(m_hp <= 0)
	{
		gameObject->SetActive(false);
		static_cast<BoxCollider*>(gameObject->GetComponent("BoxCollider"))->DeregisterCollider();
		m_playerInven->AddPoints(1);
		m_audio->Play();
	}
}

void Sniper::OnCollisionEnter(GameObject* other)
{
	if(other->GetTag() == "PlayerBullet")
	{
		m_hp -= 1;
	}
	else if(other->GetTag() == "PlayerSuperPunch")
	{
		m_hp -= 5;
	}
}

std::unique_ptr<Component> Sniper::copy()
{
	return std::make_unique<Sniper>(gameObject, m_scene, m_playerInven, m_audio);
}

bool Sniper::IsShooting() const
{
	return m_shooting;
}
