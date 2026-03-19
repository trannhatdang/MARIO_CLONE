#ifndef GROW_BIG_H_
#define GROW_BIG_H_

#include "engine/Components/Component.h"
#include "engine/Components/SpriteRenderer.h"

class GrowBig : public Component
{
	private:
		bool m_isBig = false;
		SpriteRenderer* m_spr = nullptr;
	public:
		GrowBig(GameObject* obj);
		~GrowBig();
		void OnIterate();
		std::unique_ptr<Component> copy();

		void TurnOn();
		void TurnOff();
};

#endif
