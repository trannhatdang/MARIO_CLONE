#include "CustomScene/MenuScene/SlowMovingBackground.h"
#include "engine/GameObject.h"


SlowMovingBackground::SlowMovingBackground(GameObject* obj) : Component("SlowMovingBackground", obj)
{

}

SlowMovingBackground::~SlowMovingBackground()
{

}

void SlowMovingBackground::OnIterate()
{
	Transform* tfs = gameObject->GetTransform();
	Vector3 pos = tfs->GetPosition();

	if((pos - m_new_pos).sqrMagnitude() < 5)
	{
		m_new_pos = Vector3(rand() % 200, rand() % 200, 0);
		m_unit_vec = Vector3_GetUnitVector(m_new_pos);
	}

	tfs->SetPosition(pos + m_unit_vec);
}

std::unique_ptr<Component> SlowMovingBackground::copy()
{
	return std::make_unique<SlowMovingBackground>(gameObject);
}
