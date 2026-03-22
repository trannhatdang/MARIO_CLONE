#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "engine/Components/Component.h"
#include "engine/Components/Transform.h"
#include "engine/Components/Rigidbody.h"
#include "engine/dg_time.h"

class Movement : public Component
{
	private:
		Transform* m_tfs;
		Rigidbody* m_rb;

		float m_jumpForce = 30.0f;
		float m_timeSinceLastMovement = 0.0f;
		float m_movementDelay = 0.05f;
		float m_speed = 10.0f;
		bool m_onGround = false;
		bool m_holdingLeft = false;
		bool m_holdingRight = false;
		bool m_isFacingLeft = false;
		bool m_isRunning = false;

		void moveLeft();
		void moveRight();
		void jump();
	public:
		Movement(GameObject* obj, float jumpForce = 30.0f, float m_movementDelay = 0.05f, float m_speed = 3.0f);
		~Movement();
		void OnIterate();
		void OnEvent(SDL_Event* event);
		void OnCollisionEnter(GameObject* obj);
		std::unique_ptr<Component> copy();

		bool IsOnGround() const;
		bool IsFacingLeft() const;
		bool IsRunning() const;
};

#endif
