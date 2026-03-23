#ifndef GRAVITY_H_
#define GRAVITY_H_

#include "engine/Components/Component.h"
#include "engine/Components/Rigidbody.h"

class Gravity : public Component
{
	private:
		Rigidbody* m_rb;

		float m_gravityScale = 1.0f;
	public:
		Gravity(GameObject* obj, float gravityScale = 1.0f);
		~Gravity();
		void OnIterate();
		void OnFixedIterate();
		std::unique_ptr<Component> copy();
};

#endif
