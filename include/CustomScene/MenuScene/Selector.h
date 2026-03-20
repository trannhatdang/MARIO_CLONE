#ifndef SELECTOR_H_
#define SELECTOR_H_

#include "engine/Components/Component.h"
#include "engine/Components/Transform.h"
#include "engine/Components/UI/Button.h"

class Selector : public Component
{
	private:
		std::vector<GameObject*> m_objs;

		Transform* m_tfs;
	public:
		Selector(GameObject* obj, std::vector<GameObject*> objs);
		~Selector();
		void OnIterate();
		std::unique_ptr<Component> copy();
};

#endif
