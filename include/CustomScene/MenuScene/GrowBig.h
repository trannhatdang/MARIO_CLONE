#ifndef GROW_BIG_H_
#define GROW_BIG_H_

#include "engine/Components/Component.h"

class GrowBig : public Component
{
	private:
		bool m_isBig = false;
	public:
		GrowBig(GameObject* obj);
		~GrowBig();
		void OnIterate();
		std::unique_ptr<Component> copy();
};

#endif
