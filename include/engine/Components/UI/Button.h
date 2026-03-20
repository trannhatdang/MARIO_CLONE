#ifndef UI_H_
#define UI_H_

#include "../Component.h"
#include "../SpriteRenderer.h"

class Button : public Component
{
	private:
		void (*m_onClick)() = nullptr;
		SpriteRenderer* m_spr;
		SDL_Rect m_rect;

		bool m_isHovered = false;
	public:
		Button(GameObject* obj, void (*onClick)() = nullptr);
		~Button();
		void OnIterate();
		void OnEvent(SDL_Event* event);
		std::unique_ptr<Component> copy();

		bool IsHovered() const;
};

#endif
