#ifndef GROW_BIG_H_
#define GROW_BIG_H_

#include "engine/Components/Component.h"
#include "engine/Components/SpriteRenderer.h"
#include "engine/dg_time.h"

class GrowBig : public Component
{
	private:
		SpriteRenderer* m_spr = nullptr;
		SDL_FRect m_onRect;

		void (*m_callBackFunc)() = nullptr;

		float m_timeSinceLastGrowth = 0.0f;
		float m_delay = 0.0001f;

		int m_currScale = 0;
		bool m_isBig = false;
	public:
		GrowBig(GameObject* obj, SDL_FRect onRect, float delay = 0.1f);
		~GrowBig();
		void OnIterate();
		std::unique_ptr<Component> copy();

		void TurnOn(void (*callBackFunc)() = nullptr);
		void TurnOff(void (*callBackFunc)() = nullptr);
};

#endif
