#include "CustomScene/MenuScene/Selector.h"
#include "engine/GameObject.h"

Selector::Selector(GameObject* obj, std::vector<GameObject*> objs) : Component("Selector", obj), m_objs(objs)
{
	m_tfs = gameObject->GetTransform();
	m_spr = static_cast<SpriteRenderer*>(gameObject->GetComponent("SpriteRenderer"));
}

Selector::~Selector()
{

}

void Selector::OnIterate()
{
	if(!m_spr)
	{
		return;
	}

	for(auto obj : m_objs)
	{
		auto btn = static_cast<Button*>(obj->GetComponent("Button"));
		if(!btn)
		{
			continue;
		}

		if(btn->IsHovered())
		{
			Vector3 other_pos = obj->GetTransform()->GetPosition();
			SDL_Rect other_viewport = static_cast<SpriteRenderer*>(obj->GetComponent("SpriteRenderer"))->GetViewport();

			Vector3 new_pos = { other_viewport.x - 50, other_viewport.y + 50, 0};

			m_tfs->SetPosition(new_pos);
			m_spr->SetActive(true);
			return;
		}
	}

	m_spr->SetActive(false);
}

std::unique_ptr<Component> Selector::copy()
{
	return std::make_unique<Selector>(gameObject, m_objs);
}
