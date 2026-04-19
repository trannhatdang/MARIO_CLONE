#ifndef PLAYER_BULLET_H_
#define PLAYER_BULLET_H_

#include "engine/Components/Component.h"
#include "engine/Components/Transform.h"
#include "engine/dg_time.h"

class PlayerBullet : public Component
{
	private:
		Transform* m_tfs;

		Vector3 m_dir;
		float m_delay;
		float m_timeSinceLastMovement;
	public:
		PlayerBullet(GameObject* obj, Vector3, float);
		~PlayerBullet();
		void OnIterate();
		void OnCollisionEnter(GameObject* other);
		void OnTriggerEnter(GameObject* other);
		std::unique_ptr<Component> copy();
};

#endif
