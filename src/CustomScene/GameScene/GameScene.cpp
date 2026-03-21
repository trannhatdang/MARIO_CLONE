#include "CustomScene/GameScene/GameScene.h"

using json = nlohmann::json;

const int SKY_TILE = 0;
const int GRASS_TILE = 1;
const int GROUND_TILE = 2;
const int BLOCK_TILE = 3;

const int ROCKET_SPAWNER = 0;
const int SNIPER = 1;

const int TILE_SIZE = 50;

int currSave = 0;

SDL_FRect tile_dstrect = { 0, 0, TILE_SIZE, TILE_SIZE };

std::vector<GameObject*> world1;

bool IsSniperShooting(GameObject* obj)
{
	Sniper* sniper = static_cast<Sniper*>(obj->GetComponent("Sniper"));

	return sniper->IsShooting();
}

bool IsSniperIdle(GameObject* obj)
{
	Sniper* sniper = static_cast<Sniper*>(obj->GetComponent("Sniper"));

	return !sniper->IsShooting();
}

void SetActiveWorld1(bool val)
{
	for(auto it : world1)
	{
		it->SetActive(val);
	}
}

void SpawnEnemy1(const std::unique_ptr<Scene>& gameScene)
{
	SDL_Renderer* renderer = gameScene->GetRenderer();
	std::vector<std::vector<int>> enemy1_map = GetMapFromCsv(GetEnemyWorld1Csv());
	int m = enemy1_map.size();
	for(int i = 0; i < m; ++i)
	{
		int n = enemy1_map[i].size();
		for(int j = 0; j < n; ++j)
		{
			switch(enemy1_map[i][j])
			{
				case ROCKET_SPAWNER:
					{
						auto rocketSpawner = gameScene->AddGameObject("RocketSpawner", "Spawner");
						rocketSpawner->AddComponent(new RocketSpawner(rocketSpawner, gameScene.get()));
						rocketSpawner->GetTransform()->SetPosition({ TILE_SIZE * i, TILE_SIZE * j, 0 });
					}

					break;
				case SNIPER:
					{
						auto sniper = gameScene->AddGameObject("Sniper", "Sniper");
						sniper->AddComponent(new Sniper(sniper, gameScene.get()));
						sniper->GetTransform()->SetPosition({ TILE_SIZE * i, TILE_SIZE * j, 0 });
						Animator* sniperAnim = static_cast<Animator*>(sniper->AddComponent(new Animator(sniper, renderer)));

						sniperAnim->AddAnimation(nullptr, GetSniperSpriteSheet(), { 0, 0, 100, 100 }, { 0, 0, 100, 100 }, 0, 1, &IsSniperShooting);
					}

					break;
				default:
					break;
			}
		}
	}
}

void SpawnBoss1(const std::unique_ptr<Scene>& gameScene)
{

}

void GenerateWorld1(const std::unique_ptr<Scene>& gameScene)
{
	SDL_Renderer* renderer = gameScene->GetRenderer();

	std::vector<std::vector<int>> world1_map = GetMapFromCsv(GetWorld1Csv());

	auto tilemap = gameScene->AddGameObject("Tilemap", "Tilemap");
	tilemap->AddComponent(new Tilemap(tilemap, renderer, GetTilemap(), world1_map, 100, 100, 0.5));
	world1.push_back(tilemap);

	SpawnEnemy1(gameScene);
	SpawnBoss1(gameScene);

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
	//player->AddComponent(new Gravity(player));

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
