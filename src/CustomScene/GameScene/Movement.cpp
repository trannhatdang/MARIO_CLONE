#include "CustomScene/GameScene/Movement.h"
#include "engine/GameObject.h"

Movement::Movement(GameObject* obj) : Component("Movement", obj)
{
	m_tfs = gameObject->GetTransform();
	m_rb = static_cast<Rigidbody*>(gameObject->GetComponent("Rigidbody"));
}

Movement::~Movement()
{

}

void Movement::moveLeft()
{
	Vector3 pos = m_tfs->GetPosition();
	m_rb->MovePosition(pos + Vector3(-1, 0, 0));
}

void Movement::moveRight()
{
	Vector3 pos = m_tfs->GetPosition();
	m_rb->MovePosition(pos + Vector3(1, 0, 0));
}

void Movement::moveUp()
{
	Vector3 pos = m_tfs->GetPosition();
	m_rb->MovePosition(pos + Vector3(0, -1, 0));
}

void Movement::moveDown()
{
	Vector3 pos = m_tfs->GetPosition();
	m_rb->MovePosition(pos + Vector3(0, 1, 0));
}

void Movement::OnIterate()
{

}

void Movement::OnEvent(SDL_Event* event)
{
	if(event->type == SDL_EVENT_KEY_DOWN && event->key.down)
	{
		auto keyEvent = event->key;
		if(keyEvent.key == SDLK_LEFT)
		{
			moveLeft();
		}

		if(keyEvent.key == SDLK_RIGHT)
		{
			moveRight();
		}

		if(keyEvent.key == SDLK_UP)
		{
			moveUp();
		}

		if(keyEvent.key == SDLK_DOWN)
		{
			moveDown();
		}
	}
}

std::unique_ptr<Component> Movement::copy()
{
	return std::make_unique<Movement>(gameObject);
}
