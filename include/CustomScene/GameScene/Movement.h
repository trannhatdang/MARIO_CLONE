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

		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
	public:
		Movement(GameObject* obj);
		~Movement();
		void OnIterate();
		void OnEvent(SDL_Event* event);
		std::unique_ptr<Component> copy();
};

#endif
