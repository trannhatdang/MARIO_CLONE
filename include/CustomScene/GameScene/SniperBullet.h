#ifndef SNIPER_BULLET_H_
#define SNIPER_BULLET_H_

#include "engine/Components/Component.h"
#include "engine/Components/Transform.h"
#include "engine/dg_time.h"

class SniperBullet : public Component
{
	private:
		Transform* m_tfs;

		Vector3 m_dir;
		float m_delay;
		float m_timeSinceLastMovement;
	public:
		SniperBullet(GameObject* obj, Vector3, float);
		~SniperBullet();
		void OnIterate();
		std::unique_ptr<Component> copy();
};

#endif
