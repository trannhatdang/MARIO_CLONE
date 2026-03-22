#ifndef PLAYER_H_
#define PLAYER_H_

#include "engine/Scene.h"
#include "engine/Components/Component.h"
#include "engine/Components/Rigidbody.h"
#include "engine/Components/Animator.h"
#include "engine/Components/SpriteRenderer.h"
#include "PlayerBullet.h"
#include "Movement.h"
#include "Config.h"

class Player : public Component
{
	private:
		Scene* m_scene;
		Movement* m_movement;

		float m_actDelay = 0.05f;
		float m_timeSinceLastAct = 0.0f;
		bool m_isShooting = false;
		bool m_isPunching = false;
		bool m_isRunning = false;
		bool m_isOnGround = false;

		void shoot();
		void punch();
	public:
		Player(GameObject* obj, Scene*, Movement*, float m_shootingDelay = 0.1f);
		~Player();
		void OnIterate();
		void OnEvent(SDL_Event* event);
		std::unique_ptr<Component> copy();

		bool IsFacingLeft() const;
		bool IsOnGround() const;
		bool IsRunning() const;
		bool IsShooting() const;
		bool IsPunching() const;
		bool IsActing() const;
};

#endif
