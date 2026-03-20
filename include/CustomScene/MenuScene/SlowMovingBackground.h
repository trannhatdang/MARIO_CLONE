#ifndef SLOW_MOVING_BACKGROUND_H_
#define SLOW_MOVING_BACKGROUND_H_

#include "engine/Components/Component.h"
#include "engine/Components/Transform.h"
#include "engine/dg_time.h"

class SlowMovingBackground : public Component
{
	private:
		Transform* m_tfs;

		Vector3 m_new_pos;
		Vector3 m_unit_vec;

		float m_timeSinceLastUpdate = 0.0f;
		float m_delay = 0.05f;
	public:
		SlowMovingBackground(GameObject* obj);
		~SlowMovingBackground();
		void OnIterate();
		std::unique_ptr<Component> copy();
};

#endif
