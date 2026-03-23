#include "CustomScene/GameScene/Player.h"

Player::Player(GameObject* obj, Scene* scene, Movement* movement, PlayerInventory* inven, float actDelay) : Component("Player", obj), m_scene(scene), m_movement(movement), m_inven(inven), m_actDelay(actDelay)
{

}

Player::~Player()
{

}

void Player::shoot()
{
	if(!m_scene)
	{
		return;
	}
	Vector3 cameraPos = GetCameraPos();
	Vector3 playerPos = gameObject->GetTransform()->GetPosition();
	playerPos = playerPos + cameraPos;
	playerPos.y += 25;
	playerPos.x += m_movement->IsFacingLeft() ? -25 : 25 ;

	Vector3 dir = m_movement->IsFacingLeft() ? Vector3(-1, 0, 0) : Vector3(1, 0, 0);

	auto newBullet = m_scene->AddGameObject("Bullet", "PlayerBullet");
	newBullet->GetTransform()->SetPosition(playerPos);
	newBullet->AddComponent(new SpriteRenderer(newBullet, m_scene->GetRenderer(), GetPlayerBulletSprite(), { 0, 0, 0 }, { 0, 0, 100, 100 }, { 0, 0, 25, 25 }));
	newBullet->AddComponent(new PlayerBullet(newBullet, dir, 0.01f));
	newBullet->AddComponent(new BoxCollider(newBullet, { 25, 25 }));
}

void Player::punch()
{
	if(!m_scene)
	{
		return;
	}
	Vector3 playerPos = gameObject->GetTransform()->GetPosition();

	Vector3 pos = playerPos + (m_movement->IsFacingLeft() ? Vector3(-37, 25, 0) : Vector3(50, 25, 0));

	auto newPunch = m_scene->AddGameObject("PlayerPunch", m_inven->HasSuperPunch() ? "PlayerSuperPunch" : "Punch");
	newPunch->GetTransform()->SetPosition(pos);
	newPunch->AddComponent(new BoxCollider(newPunch, { 37, 17 }));
	newPunch->AddComponent(new PlayerPunch(newPunch));
}

void Player::OnIterate()
{
	// Vector3 playerPos = gameObject->GetTransform()->GetPosition();
	//std::cout << "player pos: " << playerPos << std::endl;

	m_timeSinceLastAct += DGTime_deltaTime();

	if(m_timeSinceLastAct >= m_actDelay)
	{
		m_isShooting = false;
		m_isPunching = false;
	}

}

void Player::OnEvent(SDL_Event* event)
{
	if(!m_scene)
	{
		return;
	}

	if(event->type == SDL_EVENT_KEY_DOWN && event->key.down)
	{
		auto keyEvent = event->key;
		if(keyEvent.key == SDLK_C && !IsActing())
		{
			shoot();

			m_isShooting = true;
			m_timeSinceLastAct = 0.0f;
		}
		else if(keyEvent.key == SDLK_X && !IsActing())
		{
			punch();

			m_isPunching = true;
			m_timeSinceLastAct = 0.0f;
		}
	}

}

void Player::OnCollisionEnter(GameObject* other)
{
}

void Player::OnTriggerEnter(GameObject* other)
{
	std::cout << "hi" << std::endl;
	if(other->GetTag() == "Star")
	{
		m_inven->AddPoints(10);
	}
	else if(other->GetTag() == "SuperPunch")
	{
		m_inven->SetPunch();
	}
	else if(other->GetTag() == "SniperBullet")
	{
		m_inven->AddPoints(-1);
	}
}

std::unique_ptr<Component> Player::copy()
{
	return std::make_unique<Player>(gameObject, m_scene, m_movement, m_inven);
}

bool Player::IsFacingLeft() const
{
	return m_movement->IsFacingLeft();
}

bool Player::IsOnGround() const
{
	return m_movement->IsOnGround();
}

bool Player::IsShooting() const
{
	return m_isShooting;
}

bool Player::IsPunching() const
{
	return m_isPunching;
}

bool Player::IsRunning() const
{
	return m_movement->IsRunning();
}

bool Player::IsActing() const
{
	return m_isShooting || m_isPunching;
}
