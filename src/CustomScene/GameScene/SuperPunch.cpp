#include "CustomScene/GameScene/SuperPunch.h"
#include "engine/GameObject.h"

SuperPunch::SuperPunch(GameObject* obj) : Component("SuperPunch", obj)
{
	
}

SuperPunch::~SuperPunch()
{
	
}

void SuperPunch::OnIterate()
{

}

void SuperPunch::OnCollisionEnter(GameObject* other)
{
	gameObject->SetActive(false);
}

std::unique_ptr<Component> SuperPunch::copy()
{
	return std::make_unique<SuperPunch>(gameObject);
}
