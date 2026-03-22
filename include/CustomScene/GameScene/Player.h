#ifndef PLAYER_H_
#define PLAYER_H_

#include "engine/Components/Component.h"
#include "engine/Components/Rigidbody.h"

class Player : public Component
{
	public:
		Player(GameObject* obj);
		~Player();
		void OnIterate();
		std::unique_ptr<Component> copy();
};

#endif
