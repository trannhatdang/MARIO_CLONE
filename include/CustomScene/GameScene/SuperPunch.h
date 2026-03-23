#ifndef SUPER_PUNCH_H_
#define SUPER_PUNCH_H_

#include "engine/Components/Component.h"

class SuperPunch : public Component
{
	public:
		SuperPunch(GameObject*);
		~SuperPunch();
		void OnIterate();
		void OnCollisionEnter(GameObject* other);
		void OnTriggerEnter(GameObject* other);
		std::unique_ptr<Component> copy();
};

#endif
