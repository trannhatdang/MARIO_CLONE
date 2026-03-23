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
	std::cout << "HI" << std::endl;
	gameObject->SetActive(false);
}

std::unique_ptr<Component> Star::copy()
{
	return std::make_unique<Star>(gameObject);
}
