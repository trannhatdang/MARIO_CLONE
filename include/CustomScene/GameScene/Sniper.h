#ifndef SNIPER_H_
#define SNIPER_H_

#include "engine/Components/Component.h"
#include "engine/Scene.h"

class Sniper : public Component
{
	private:
		Scene* m_scene;

		float m_shootingTime = 1.0f;
		float m_shootDelay = 0.5f;

		bool m_shooting = false;
	public:
		Sniper(GameObject* obj, Scene* currScene);
		~Sniper();
		void OnIterate();
		std::unique_ptr<Component> copy();

		bool IsShooting() const;
};

#endif
