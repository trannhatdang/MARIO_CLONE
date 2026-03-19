#include "engine/Components/UI/Button.h"
#include "engine/GameObject.h"

Button::Button(GameObject* obj, void (*onClick)()) : Component("Button", obj), m_onClick(onClick)
{
	m_spr = static_cast<SpriteRenderer*>(gameObject->GetComponent("SpriteRenderer"));
	if(!m_spr)
	{
		return;
	}

	m_rect = m_spr->GetDstRect();
}

Button::~Button()
{

}

void Button::OnIterate()
{

}

void Button::OnEvent(SDL_Event* event)
{
	if(!m_spr) return;

	if(event->type != SDL_EVENT_MOUSE_BUTTON_DOWN || !event->key.down)
	{
		return;
	}

	auto mouseEvent = event->button;

	float x = mouseEvent.x;
	float y = mouseEvent.y;

	Vector3 pos = Vector3(x, y, 0);

	if(IsPointInsideRect(pos, m_rect))
	{
		(*m_onClick)();
	};
}

std::unique_ptr<Component> Button::copy()
{
	return std::make_unique<Button>(gameObject);
}
