#include "CustomScene/GameScene/Movement.h"
#include "engine/GameObject.h"

Movement::Movement(GameObject* obj, float jumpForce, float movementDelay, float speed) : Component("Movement", obj), m_jumpForce(jumpForce), m_movementDelay(movementDelay), m_speed(speed)
{
	m_tfs = gameObject->GetTransform();
	m_rb = static_cast<Rigidbody*>(gameObject->GetComponent("Rigidbody"));
}

Movement::~Movement()
{

}

void Movement::moveLeft()
{
	if(m_timeSinceLastMovement < m_movementDelay)
	{
		return;
	}
	m_timeSinceLastMovement = 0.0f;

	Vector3 pos = m_tfs->GetPosition();
	m_rb->MovePosition(pos + Vector3(-m_speed, 0, 0));

	// Vector3f dir = { m_speed, 0, 0 };
	// m_rb->AddForce(dir);
}

void Movement::moveRight()
{
	if(m_timeSinceLastMovement < m_movementDelay)
	{
		return;
	}
	m_timeSinceLastMovement = 0.0f;

	Vector3 pos = m_tfs->GetPosition();
	m_rb->MovePosition(pos + Vector3(m_speed, 0, 0));

	// Vector3f dir = { m_speed, 0, 0 };
	// m_rb->AddForce(dir);
}

void Movement::jump()
{
	if(!m_onGround)
	{
		return;
	}

	m_onGround = false;

	// if(m_holdingLeft)
	// {
	// 	m_rb->AddForce({ -1.0f * m_jumpForce * 0.707f, -m_jumpForce * 0.707f, 0 });
	// }
	// else if(m_holdingRight)
	// {
	// 	m_rb->AddForce({ 1.0f * m_jumpForce * 0.707f, -m_jumpForce * 0.707f, 0 });
	// }
	// else
	{
		m_rb->AddForce({ 0, -m_jumpForce, 0 });
	}
}

void Movement::OnIterate()
{
	m_timeSinceLastMovement += DGTime_deltaTime();
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

			m_holdingLeft = true;
		}
		else if(keyEvent.key == SDLK_RIGHT)
		{
			moveRight();
			m_isFacingLeft = false;
			m_isRunning = true;

			m_holdingRight = true;
		}

	}
	else if(event->type == SDL_EVENT_KEY_UP && !event->key.down)
	{
		auto keyEvent = event->key;
		if(keyEvent.key == SDLK_LEFT)
		{
			m_isRunning = false;
			m_holdingLeft = false;
		}
		else if(keyEvent.key == SDLK_RIGHT)
		{
			m_isRunning = false;
			m_holdingRight = false;
		}

		if(keyEvent.key == SDLK_SPACE)
		{
			jump();
		}
	}
}

std::unique_ptr<Component> Movement::copy()
{
	return std::make_unique<Movement>(gameObject);
}

void Movement::OnCollisionEnter(GameObject* obj)
{
	if(obj->GetTag() == "Collider")
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
