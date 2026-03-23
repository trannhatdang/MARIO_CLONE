#ifndef SNIPER_H_
#define SNIPER_H_

#include "engine/Components/Component.h"
#include "engine/Components/SpriteRenderer.h"
#include "engine/Scene.h"
#include "engine/dg_time.h"
#include "SniperBullet.h"
#include "PlayerInventory.h"
#include "Config.h"

class Sniper : public Component
{
	private:
		Scene* m_scene;
		PlayerInventory* m_playerInven;

		int m_hp = 5;
		float m_shootingTime = 1.0f;
		float m_shootDelay = 0.5f;
		float m_timeSinceStartedShooting = 0.0f;
		float m_timeSinceLastShot = 0.0f;

		bool m_shooting = false;

		void shoot();
	public:
		Sniper(GameObject* obj, Scene* currScene, PlayerInventory*);
		~Sniper();
		void OnIterate();
		void OnCollisionEnter(GameObject* other);
		std::unique_ptr<Component> copy();

		bool IsShooting() const;
};

#endif
