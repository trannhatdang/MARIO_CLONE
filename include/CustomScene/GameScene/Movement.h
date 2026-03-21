#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "engine/Components/Component.h"
#include "engine/Components/Transform.h"
#include "engine/Components/Rigidbody.h"

class Movement : public Component
{
	private:
		Transform* m_tfs;
		Rigidbody* m_rb;

		float m_jumpForce = 1.0f;
		bool m_onGround = false;

		void moveLeft();
		void moveRight();
		void jump();
	public:
		Movement(GameObject* obj, float jumpForce = 1.0f);
		~Movement();
		void OnIterate();
		void OnEvent(SDL_Event* event);
		void OnCollisionEnter(GameObject* obj);
		std::unique_ptr<Component> copy();
};

#endif
