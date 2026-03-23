#ifndef STAR_H_
#define STAR_H_

#include "engine/Components/Component.h"

class Star : public Component
{
	public:
		Star(GameObject*);
		~Star();
		void OnIterate();
		void OnCollisionEnter(GameObject* other);
		std::unique_ptr<Component> copy();
};

#endif
