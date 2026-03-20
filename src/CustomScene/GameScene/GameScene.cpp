#include "CustomScene/GameScene/GameScene.h"

using json = nlohmann::json;

int currSave = 0;

void GenerateGameScene(const std::unique_ptr<Scene>& gameScene, int (*getCurrSaveFunc)())
{
	std::fstream f(GetSaveFile());
	json save_data = json::parse(f);

	int world1 = save_data["save1"]["world"];
	int world2 = save_data["save2"]["world"];

	int currWorld = 1;

	if(currSave == 1)
	{
		currWorld = world1;
	}
	else
	{
		currWorld = world2;
	}



}
