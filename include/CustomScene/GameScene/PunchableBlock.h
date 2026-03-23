#ifndef PUNCHABLE_BLOCK_H_
#define PUNCHABLE_BLOCK_H_

#include "engine/Components/Component.h"

class PunchableBlock : public Component
{
	public:
		PunchableBlock(GameObject*);
		~PunchableBlock();
		void OnIterate();
		void OnCollisionEnter(GameObject* other);
		std::unique_ptr<Component> copy();
};

#endif
