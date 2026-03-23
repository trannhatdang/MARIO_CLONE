#ifndef BOSS_H_
#define BOSS_H_

#include "engine/Components/Component.h"
#include "engine/Components/SpriteRenderer.h"
#include "engine/Components/BoxCollider.h"
#include "engine/Scene.h"
#include "engine/dg_time.h"
#include "PlayerInventory.h"
#include "SniperBullet.h"
#include "Config.h"

class Boss : public Component
{
	private:
		Scene* m_scene;
		PlayerInventory* m_inven;

		int m_hp = 10000;

		int m_left;
		int m_right;
		int m_up = 0;
		int m_down = 560;

		float m_timeSinceLastShooting = 0.0f;
		float m_shootingTimeDelay = 5.0f;
		float m_timeSinceStartedShooting = 0.0f;
		float m_shootingTime = 2.5f;

		float m_timeSinceLastShot = 0.0f;
		float m_shotDelay = 1.0f;

		bool m_shooting = false;
		bool m_movingLeft = false;

		void shoot();
	public:
		Boss(GameObject*, Scene*, PlayerInventory*, int, int);
		~Boss();
		void OnIterate();
		std::unique_ptr<Component> copy();
		void OnCollisionEnter(GameObject* obj);
};

#endif
