#ifndef SLOW_MOVING_BACKGROUND_H_
#define SLOW_MOVING_BACKGROUND_H_

#include "engine/Components/Component.h"

class SlowMovingBackground : public Component
{
	private:
		Vector3 m_new_pos;
		Vector3 m_unit_vec;
	public:
		SlowMovingBackground(GameObject* obj);
		~SlowMovingBackground();
		void OnIterate();
		std::unique_ptr<Component> copy();
};

#endif
