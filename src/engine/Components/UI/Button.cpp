#include "engine/Components/UI/Button.h"

Button::Button(GameObject* obj, void (*onClick)()) : Component("Button", obj), m_onClick(onClick)
{

}

Button::~Button()
{

}

void Button::OnIterate()
{

}

std::unique_ptr<Component> Button::copy()
{
	return std::make_unique<Button>(gameObject);
}
