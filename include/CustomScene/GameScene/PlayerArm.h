#ifndef PLAYER_ARM_H_
#define PLAYER_ARM_H_

#include "engine/Components/Component.h"
#include "engine/Components/Rigidbody.h"
#include "engine/Components/Transform.h"

class PlayerArm : public Component
{
	private:
		GameObject* m_player;
		Transform* m_tfs;
		Transform* m_playerTfs;
	public:
		PlayerArm(GameObject* obj, GameObject* player);
		~PlayerArm();
		void OnIterate();
		std::unique_ptr<Component> copy();
};

#endif
