#include "CustomScene/GameScene/DestructibleBlock.h"
#include "engine/GameObject.h"

DestructibleBlock::DestructibleBlock(GameObject* obj, Scene* scene, SDL_Renderer* renderer, bool hasItems, bool star) : Component("DestructibleBlock", obj), m_scene(scene), m_renderer(renderer), m_hasItems(hasItems), m_star(star)
{
	
}

DestructibleBlock::~DestructibleBlock()
{
	
}

void DestructibleBlock::OnIterate()
{

}

void DestructibleBlock::OnCollisionEnter(GameObject* other)
{
	if(!(other->GetTag() == "PlayerBullet" || other->GetTag() == "Punch" || other->GetTag() == "SuperPunch"))
	{
		return;
	}

	if(!m_hasItems)
	{
		return;
	}
	
	GameObject* newGb;
	if(m_star)
	{
		newGb = m_scene->AddGameObject("Star", "Star");
		newGb->AddComponent(new Star(newGb));
		newGb->AddComponent(new SpriteRenderer(newGb, m_renderer, GetStarSprite(), { 0, 0, 0 }, { 0, 0, 100, 100 }, { 0, 0, 25, 25 }));
	}
	else
	{
		newGb = m_scene->AddGameObject("SuperPunch", "SuperPunch");
		newGb->AddComponent(new SuperPunch(newGb));
		newGb->AddComponent(new SpriteRenderer(newGb, m_renderer, GetSuperPunchSprite(), { 0, 0, 0 }, { 0, 0, 100, 100 }, { 0, 0, 25, 25 }));
	}
	newGb->AddComponent(new BoxCollider(newGb, { 25, 25 }, false, true));
	newGb->GetTransform()->SetPosition(gameObject->GetTransform()->GetPosition());

	gameObject->SetActive(false);
}

std::unique_ptr<Component> DestructibleBlock::copy()
{
	return std::make_unique<DestructibleBlock>(gameObject, m_scene, m_renderer, m_hasItems, m_star);
}
