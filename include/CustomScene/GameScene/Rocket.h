#ifndef ROCKET_H_
#define ROCKET_H_

#include "engine/Components/Component.h"
#include "engine/Components/Transform.h"

class Rocket : public Component
{
	private:
		Transform* m_tfs;
	public:
		Rocket(GameObject* obj);
		~Rocket();
		void OnIterate();
		std::unique_ptr<Component> copy();
};

#endif
