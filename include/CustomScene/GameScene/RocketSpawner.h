#ifndef ROCKET_SPAWNER_H_
#define ROCKET_SPAWNER_H_

#include "engine/Components/Component.h"
#include "engine/Components/SpriteRenderer.h"
#include "engine/Components/BoxCollider.h"
#include "engine/dg_time.h"
#include "engine/Scene.h"
#include "Config.h"
#include "Rocket.h"

class RocketSpawner : public Component
{
	private:
		Scene* m_currScene;

		float m_timeSinceLastSpawn = 0.0f;
		float m_delay = 10.0f;

		void spawnRocket();
	public:
		RocketSpawner(GameObject* obj, Scene* currScene);
		~RocketSpawner();
		void OnIterate();
		std::unique_ptr<Component> copy();
};

#endif
