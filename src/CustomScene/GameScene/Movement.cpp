#include "CustomScene/GameScene/Movement.h"
#include "engine/GameObject.h"

Movement::Movement(GameObject* obj, float jumpForce, float movementDelay) : Component("Movement", obj), m_jumpForce(jumpForce), m_movementDelay(movementDelay)
{
	m_tfs = gameObject->GetTransform();
	m_rb = static_cast<Rigidbody*>(gameObject->GetComponent("Rigidbody"));
}

Movement::~Movement()
{

}

void Movement::moveLeft()
{
	m_timeSinceLastMovement += DGTime_deltaTime();
	if(m_timeSinceLastMovement < m_movementDelay)
	{
		return;
	}

	Vector3 pos = m_tfs->GetPosition();
	m_tfs->SetPosition(pos + Vector3(-1, 0, 0));
}

void Movement::moveRight()
{
	m_timeSinceLastMovement += DGTime_deltaTime();
	if(m_timeSinceLastMovement < m_movementDelay)
	{
		return;
	}

	Vector3 pos = m_tfs->GetPosition();
	m_tfs->SetPosition(pos + Vector3(1, 0, 0));
}

void Movement::jump()
{
	if(!m_onGround)
	{
		return;
	}

	m_rb->AddForce(Vector3(0, m_jumpForce, 0));
	m_onGround = false;
}

void Movement::OnIterate()
{

}

void Movement::OnEvent(SDL_Event* event)
{
	if(!m_rb)
	{
		return;
	}

	if(event->type == SDL_EVENT_KEY_DOWN && event->key.down)
	{
		auto keyEvent = event->key;
		if(keyEvent.key == SDLK_LEFT)
		{
			moveLeft();
			m_isFacingLeft = true;
			m_isRunning = true;
		}
		else if(keyEvent.key == SDLK_RIGHT)
		{
			moveRight();
			m_isFacingLeft = false;
			m_isRunning = true;
		}
		else if(keyEvent.key == SDLK_SPACE)
		{
			jump();
		}
	}
	else if(event->type == SDL_EVENT_KEY_DOWN && event->key.down)
	{
		auto keyEvent = event->key;
		if(keyEvent.key == SDLK_LEFT)
		{
			m_isRunning = false;
		}
		else if(keyEvent.key == SDLK_RIGHT)
		{
			m_isRunning = false;
		}
	}
}

std::unique_ptr<Component> Movement::copy()
{
	return std::make_unique<Movement>(gameObject);
}

void Movement::OnCollisionEnter(GameObject* obj)
{
	if(obj->GetTag() == "Floor")
	{
		m_onGround = true;
	}
}

bool Movement::IsOnGround() const
{
	return m_onGround;
}

bool Movement::IsFacingLeft() const
{
	return m_isFacingLeft;
}

bool Movement::IsRunning() const
{
	return m_isRunning;
}
