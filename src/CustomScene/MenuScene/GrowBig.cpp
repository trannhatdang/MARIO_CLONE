#include "CustomScene/MenuScene/GrowBig.h"

GrowBig::GrowBig(GameObject* obj) : Component("GrowBig", obj)
{

}

GrowBig::~GrowBig()
{

}

void GrowBig::OnIterate()
{

}

std::unique_ptr<Component> GrowBig::copy()
{
	return std::make_unique<GrowBig>(gameObject);
}
