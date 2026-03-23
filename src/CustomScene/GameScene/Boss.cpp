#include "CustomScene/GameScene/Boss.h"

Boss::Boss(GameObject* obj, Scene* scene, PlayerInventory* playerInven, int left, int right) : Component("Boss", obj), m_scene(scene), m_inven(playerInven), m_left(left), m_right(right)
{

}

Boss::~Boss()
{

}

void Boss::shoot()
{
	m_timeSinceLastShot += DGTime_deltaTime();
	m_timeSinceStartedShooting += DGTime_deltaTime();
	if(m_timeSinceStartedShooting > m_shootingTime)
	{
		m_shooting = false;
		m_timeSinceLastShot = 0.0f;
		m_timeSinceStartedShooting = 0.0f;
		return;
	}

	if(m_timeSinceLastShot < m_shotDelay)
	{
		return;
	}

	Vector3 pos = gameObject->GetTransform()->GetPosition();

	auto newBullet = m_scene->AddGameObject("Bullet", "SniperBullet");
	newBullet->GetTransform()->SetPosition(pos);
	newBullet->AddComponent(new SpriteRenderer(newBullet, m_scene->GetRenderer(), GetSniperBulletSprite(), { 0, 0, 0 }, { 0, 0, 100, 100 }, { 0, 0, 25, 25 }));
	newBullet->AddComponent(new SniperBullet(newBullet, {0, -1, 0} , 0.01f));
	newBullet->AddComponent(new BoxCollider(newBullet, { 25, 25 }, true, true));

	auto newBullet1 = m_scene->AddGameObject("Bullet", "SniperBullet");
	newBullet1->GetTransform()->SetPosition(pos);
	newBullet1->AddComponent(new SpriteRenderer(newBullet1, m_scene->GetRenderer(), GetSniperBulletSprite(), { 0, 0, 0 }, { 0, 0, 100, 100 }, { 0, 0, 25, 25 }));
	newBullet1->AddComponent(new SniperBullet(newBullet1, {0, 1, 0} , 0.01f));

	auto newBullet2 = m_scene->AddGameObject("Bullet", "SniperBullet");
	newBullet2->GetTransform()->SetPosition(pos);
	newBullet2->AddComponent(new SpriteRenderer(newBullet2, m_scene->GetRenderer(), GetSniperBulletSprite(), { 0, 0, 0 }, { 0, 0, 100, 100 }, { 0, 0, 25, 25 }));
	newBullet2->AddComponent(new SniperBullet(newBullet2, {-1, 0, 0} , 0.01f));

	auto newBullet3 = m_scene->AddGameObject("Bullet", "SniperBullet");
	newBullet3->GetTransform()->SetPosition(pos);
	newBullet3->AddComponent(new SpriteRenderer(newBullet3, m_scene->GetRenderer(), GetSniperBulletSprite(), { 0, 0, 0 }, { 0, 0, 100, 100 }, { 0, 0, 25, 25 }));
	newBullet3->AddComponent(new SniperBullet(newBullet3, {1, 0, 0} , 0.01f));

	auto newBullet4 = m_scene->AddGameObject("Bullet", "SniperBullet");
	newBullet4->GetTransform()->SetPosition(pos);
	newBullet4->AddComponent(new SpriteRenderer(newBullet4, m_scene->GetRenderer(), GetSniperBulletSprite(), { 0, 0, 0 }, { 0, 0, 100, 100 }, { 0, 0, 25, 25 }));
	newBullet4->AddComponent(new SniperBullet(newBullet4, {1, -1, 0} , 0.01f));

	auto newBullet5 = m_scene->AddGameObject("Bullet", "SniperBullet");
	newBullet5->GetTransform()->SetPosition(pos);
	newBullet5->AddComponent(new SpriteRenderer(newBullet5, m_scene->GetRenderer(), GetSniperBulletSprite(), { 0, 0, 0 }, { 0, 0, 100, 100 }, { 0, 0, 25, 25 }));
	newBullet5->AddComponent(new SniperBullet(newBullet5, {1, 1, 0} , 0.01f));

	auto newBullet6 = m_scene->AddGameObject("Bullet", "SniperBullet");
	newBullet6->GetTransform()->SetPosition(pos);
	newBullet6->AddComponent(new SpriteRenderer(newBullet6, m_scene->GetRenderer(), GetSniperBulletSprite(), { 0, 0, 0 }, { 0, 0, 100, 100 }, { 0, 0, 25, 25 }));
	newBullet6->AddComponent(new SniperBullet(newBullet6, {-1, -1, 0} , 0.01f));

	auto newBullet7 = m_scene->AddGameObject("Bullet", "SniperBullet");
	newBullet7->GetTransform()->SetPosition(pos);
	newBullet7->AddComponent(new SpriteRenderer(newBullet7, m_scene->GetRenderer(), GetSniperBulletSprite(), { 0, 0, 0 }, { 0, 0, 100, 100 }, { 0, 0, 25, 25 }));
	newBullet7->AddComponent(new SniperBullet(newBullet7, {-1, 1, 0} , 0.01f));
}

void Boss::OnIterate()
{
	if(m_shooting)
	{
		shoot();
		return;
	}

	m_timeSinceLastShooting += DGTime_deltaTime();
	if(m_timeSinceLastShooting > m_shootingTimeDelay)
	{
		m_shooting = true;
		m_timeSinceLastShooting = 0.0f;
	}

	if(m_hp <= 0)
	{
		gameObject->SetActive(false);
	}
	Vector3 pos = gameObject->GetTransform()->GetRelativePosition();

	if(rand() % 200 < 5)
	{
		pos.x = std::max(m_left, std::min(m_right, pos.x + rand() % 10));
		pos.x = std::max(m_up, std::min(m_down, pos.y + rand() % 10));

		gameObject->GetTransform()->SetPosition(pos);
	}

	//
	// if(m_movingLeft)
	// {
	// 	if(pos.x <= m_left)
	// 	{
	// 		m_movingLeft = false;
	// 		return;
	// 	}
	//
	// 	gameObject->GetTransform()->SetPosition(pos + Vector3(-1, 0, 0));
	// }
	// else
	// {
	// 	if(pos.x >= m_right)
	// 	{
	// 		m_movingLeft = true;
	// 		return;
	// 	}
	// 	gameObject->GetTransform()->SetPosition(pos + Vector3(1, 0, 0));
	//
	// }
}

void Boss::OnCollisionEnter(GameObject* obj)
{
	if(obj->GetTag() == "PlayerBullet")
	{
		m_hp -= 100;
	}
	else if(obj->GetTag() == "PlayerSuperPunch")
	{
		m_hp -= 10000;
		gameObject->SetActive(false);
	}
}

std::unique_ptr<Component> Boss::copy()
{
	return std::make_unique<Boss>(gameObject, m_scene, m_inven, m_left, m_right);
}
