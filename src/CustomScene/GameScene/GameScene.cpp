#include "CustomScene/GameScene/GameScene.h"

using json = nlohmann::json;

const int SKY_TILE = 0;
const int GRASS_TILE = 1;
const int GROUND_TILE = 2;
const int BLOCK_TILE = 3;

int currSave = 0;

SDL_FRect tile_dstrect = { 0, 0, 50, 50};

std::vector<GameObject*> world1;

void SetActiveWorld1(bool val)
{
	for(auto it : world1)
	{
		it->SetActive(val);
	}
}

void GenerateWorld1(const std::unique_ptr<Scene>& gameScene)
{
	SDL_Renderer* renderer = gameScene->GetRenderer();

	std::vector<std::vector<int>> world1_map = GetMapFromCsv(GetWorld1Csv());

	auto tilemap = gameScene->AddGameObject("Tilemap", "Tilemap");
	tilemap->AddComponent(new Tilemap(tilemap, renderer, GetTilemap(), world1_map, 100, 100, 0.5));
	world1.push_back(tilemap);

	auto rocketSpawner = gameScene->AddGameObject("RocketSpawner", "Spawner");
	rocketSpawner->AddComponent(new RocketSpawner(rocketSpawner, gameScene.get()));

	SetActiveWorld1(false);
}

void GenerateGameScene(const std::unique_ptr<Scene>& gameScene, int (*getCurrSaveFunc)(), void (*setCameraPosFunc)(Vector3))
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

	GenerateWorld1(gameScene);

	auto player = gameScene->AddGameObject("Player", "Player");
	player->AddComponent(new Movement(player));
	player->AddComponent(new Rigidbody(player, false, 1, 10));
	player->AddComponent(new Gravity(player));

	auto camera = gameScene->AddGameObject("Camera", "Camera");
	camera->AddComponent(new Camera(camera, player, setCameraPosFunc));

	switch(currWorld)
	{
		case 1:
			SetActiveWorld1(true);
			break;
		default:
			break;
	}
}
