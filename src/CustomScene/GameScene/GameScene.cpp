#include "CustomScene/GameScene/GameScene.h"

using json = nlohmann::json;

const int SKY_TILE = 0;
const int GRASS_TILE = 1;
const int GROUND_TILE = 2;
const int BLOCK_TILE = 3;
const int DESTRUCTABLE_BLOCK_TILE = 4;
const int FLASHING_BLOCK_TILE = 5;

const int ROCKET_SPAWNER = 0;
const int SNIPER = 1;

const int TILE_SIZE = 50;

//int currSave = 0;

static SDL_FRect tile_dstrect = { 0, 0, TILE_SIZE, TILE_SIZE };

static std::vector<std::vector<GameObject*>> worlds;

void SetWorld(int val)
{
	for(int i = 0; i < worlds.size(); ++i)
	{
		for(int j = 0; j < worlds[i].size(); ++j)
		{
			bool active = (i == val);
			worlds[i][j]->SetActive(active);
		}
	}
}

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
						auto sniper = gameScene->AddGameObject("Sniper", "Enemy");
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

void GenerateColliders1(const std::unique_ptr<Scene>& gameScene)
{
	auto groundCol = gameScene->AddGameObject("GroundCollider", "Collider");
	groundCol->GetTransform()->SetPosition({ 50 * 7, 0, 0});
	groundCol->AddComponent(new BoxCollider(groundCol, { 50 * 36, 50 * 4 }));

	//auto penisBaseCol = gameScene->AddGameObject("PenisBaseCol", "Collider");

}

void GenerateWorld1(const std::unique_ptr<Scene>& gameScene)
{
	SDL_Renderer* renderer = gameScene->GetRenderer();

	std::vector<std::vector<int>> world1_map = GetMapFromCsv(GetWorld1Csv());

	auto tilemap = gameScene->AddGameObject("Tilemap", "Tilemap");
	tilemap->AddComponent(new Tilemap(tilemap, renderer, GetTilemap(), world1_map, 100, 100, 0.5));
	worlds[0].push_back(tilemap);

	GenerateColliders1(gameScene);
	//SpawnEnemy1(gameScene);
	//SpawnBoss1(gameScene);

	//SetActiveWorld1(false);
}

void GenerateGameScene(const std::unique_ptr<Scene>& gameScene, void (*setCameraPosFunc)(Vector3))
{
	SDL_Renderer* renderer = gameScene->GetRenderer();

	GenerateWorld1(gameScene);

	auto player = gameScene->AddGameObject("Player", "Player");
	player->AddComponent(new Player(player));

	auto bodyAnim = player->AddComponent(new Animator(player, renderer));
	auto armAnim = player->AddComponent(new Animator(player, renderer, { 0.5, 0.5, 0 }));

	player->AddComponent(new Movement(player));
	player->AddComponent(new Rigidbody(player, false, 1, 10));
	//player->AddComponent(new Gravity(player));

	auto camera = gameScene->AddGameObject("Camera", "Camera");
	camera->AddComponent(new Camera(camera, player, setCameraPosFunc));
}
