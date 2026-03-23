#include "CustomScene/GameScene/PunchableBlock.h"
#include "engine/GameObject.h"

PunchableBlock::PunchableBlock(GameObject* obj) : Component("PunchableBlock", obj)
{
	
}

PunchableBlock::~PunchableBlock()
{
	
}

void PunchableBlock::OnIterate()
{

}

void PunchableBlock::OnCollisionEnter(GameObject* other)
{
	if(other->GetTag() == "Punch" || other->GetTag() == "SuperPunch")
	{
		Transform* tfs = gameObject->GetTransform();
		Vector3 currPos = tfs->GetPosition();
		Vector3 dir = Vector3_GetUnitVector(other->GetTransform()->GetPosition() - tfs->GetPosition());

		if(dir.x >= 0)
		{
			gameObject->GetTransform()->SetPosition(currPos + Vector3(-50, 0, 0));
		}
		else
		{
			gameObject->GetTransform()->SetPosition(currPos + Vector3(50, 0, 0));
		}
	}
}

std::unique_ptr<Component> PunchableBlock::copy()
{
	return std::make_unique<PunchableBlock>(gameObject);
}
