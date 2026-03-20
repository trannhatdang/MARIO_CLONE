#include "CustomScene/MenuScene/SlowMovingBackground.h"
#include "engine/GameObject.h"

SlowMovingBackground::SlowMovingBackground(GameObject* obj) : Component("SlowMovingBackground", obj)
{
	m_tfs = gameObject->GetTransform();
	Vector3 pos = m_tfs->GetPosition();
	m_new_pos = pos + Vector3(rand() % 400 - 200, rand() % 400 - 200, 0);
}

SlowMovingBackground::~SlowMovingBackground()
{

}

void SlowMovingBackground::OnIterate()
{
	if(m_timeSinceLastUpdate < m_delay)
	{
		m_timeSinceLastUpdate += DGTime_deltaTime();
		return;
	}

	m_timeSinceLastUpdate = 0.0f;

	Vector3 pos = m_tfs->GetPosition();

	if((pos - m_new_pos).magnitude() < 200)
	{
		while((pos - m_new_pos).magnitude() < 220)
		{
			m_new_pos = pos + Vector3(rand() % 400 - 200, rand() % 400 - 200, 0);
		}
	}

	m_unit_vec = Vector3_GetUnitVector(m_new_pos - pos);
	m_tfs->SetPosition(pos + m_unit_vec);
}

std::unique_ptr<Component> SlowMovingBackground::copy()
{
	return std::make_unique<SlowMovingBackground>(gameObject);
}
