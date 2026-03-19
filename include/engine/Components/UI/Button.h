#ifndef UI_H_
#define UI_H_

#include "../Component.h"

class Button : public Component
{
	private:
		void (*m_onClick)() = nullptr;
	public:
		Button(GameObject* obj, void (*onClick)() = nullptr);
		~Button();
		void OnIterate();
		std::unique_ptr<Component> copy();
};

#endif
