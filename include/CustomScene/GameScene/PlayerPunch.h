#ifndef PLAYER_PUNCH_H_
#define PLAYER_PUNCH_H_

#include "engine/Components/Component.h"
#include "engine/dg_time.h"

class PlayerPunch : public Component
{
	private:
		float m_aliveTime = 0.0f;
		float m_timeAlive = 0.5f;
	public:
		PlayerPunch(GameObject*);
		~PlayerPunch();
		void OnIterate();
		std::unique_ptr<Component> copy();
};

#endif
