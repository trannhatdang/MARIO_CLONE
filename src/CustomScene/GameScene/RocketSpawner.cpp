#include "CustomScene/GameScene/RocketSpawner.h"

RocketSpawner::RocketSpawner(GameObject* obj, Scene* currScene) : Component("RocketSpawner", obj), m_currScene(currScene)
{

}

RocketSpawner::~RocketSpawner()
{

}

void RocketSpawner::spawnRocket()
{
	Vector3 pos = gameObject->GetTransform()->GetPosition();
	auto rocket = m_currScene->AddGameObject("Rocket", "Enemy");
	rocket->GetTransform()->SetPosition(pos);
	rocket->AddComponent(new Rocket(rocket));
	rocket->AddComponent(new BoxCollider(rocket, { 25, 25 }, false));
	rocket->AddComponent(new SpriteRenderer(rocket,
				m_currScene->GetRenderer(),
				GetRocketSprite(),
				{ 0, 0, 0 }, { 0, 0, 100, 100 }, { 0, 0, 25, 25 }));
}

void RocketSpawner::OnIterate()
{
	Vector3 pos = gameObject->GetTransform()->GetPosition();
	Vector3 cameraPos = GetCameraPos();
	SDL_Rect cameraRect = { cameraPos.x, cameraPos.y, 1120, 630 };

	if(!IsPointInsideRect(pos, cameraRect))
	{
		return;
	}

	if(m_timeSinceLastSpawn < m_delay)
	{
		m_timeSinceLastSpawn += DGTime_deltaTime();
		return;
	}

	spawnRocket();
}

std::unique_ptr<Component> RocketSpawner::copy()
{
	return std::make_unique<RocketSpawner>(gameObject, m_currScene);
}
