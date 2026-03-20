#include "CustomScene/MenuScene/Selector.h"
#include "engine/GameObject.h"

Selector::Selector(GameObject* obj, std::vector<GameObject*> objs) : Component("Selector", obj), m_objs(objs)
{
	m_tfs = gameObject->GetTransform();
}

Selector::~Selector()
{

}

void Selector::OnIterate()
{
	for(auto obj : m_objs)
	{
		auto btn = static_cast<Button*>(obj->GetComponent("Button"));
		if(!btn) continue;

		if(btn->IsHovered())
		{
			Vector3 other_pos = obj->GetTransform()->GetPosition();

			m_tfs->SetPosition(other_pos);
		}
	}
}

std::unique_ptr<Component> Selector::copy()
{
	return std::make_unique<Selector>(gameObject, m_objs);
}
