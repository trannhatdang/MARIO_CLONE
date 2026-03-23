#include "CustomScene/GameScene/Star.h"
#include "engine/GameObject.h"

Star::Star(GameObject* obj) : Component("Star", obj)
{
	
}

Star::~Star()
{
	
}

void Star::OnIterate()
{

}

void Star::OnCollisionEnter(GameObject* other)
{
	std::cout << other->GetName() << std::endl;
	if(other->GetName() == "Player")
	{
		gameObject->SetActive(false);
	}
}

void Star::OnTriggerEnter(GameObject* other)
{
	std::cout << other->GetName() << std::endl;
	if(other->GetName() == "Player")
	{
		gameObject->SetActive(false);
	}
}

std::unique_ptr<Component> Star::copy()
{
	return std::make_unique<Star>(gameObject);
}
