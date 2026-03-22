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

const int SHOOTING_ARM = 0;
const int PUNCHING_ARM = 1;
const int IDLE_ARM = 2;
const int INVIS_ARM = 3;

const int TILE_SIZE = 50;

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

bool IsIdle(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return player->IsOnGround() && !player->IsActing() && !player->IsRunning();
}

bool IsIdleActing(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return player->IsOnGround() && player->IsActing() && !player->IsRunning();
}

bool IsRunning(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return player->IsOnGround() && !player->IsActing() && player->IsRunning();
}

bool IsRunningActing(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return player->IsOnGround() && player->IsActing() && player->IsRunning();
}

bool IsJumping(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return !player->IsOnGround() && !player->IsActing();
}

bool IsJumpingActing(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return !player->IsOnGround() && player->IsActing();
}

bool IsPlayerShooting(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return player->IsOnGround() && player->IsShooting();
}

bool IsPlayerPunching(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return player->IsOnGround() && player->IsPunching();
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

						sniperAnim->AddAnimation(nullptr, GetSniperSpriteSheet(), { 0, 0, 50, 50 }, { 0, 0, 50, 50 }, 1, &IsSniperIdle, 2.0f);
						sniperAnim->AddAnimation(nullptr, GetSniperSpriteSheet(), { 100, 0, 100, 100 }, { 0, 0, 50, 50 }, 1, &IsSniperShooting, 1.0f);
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
	groundCol->GetTransform()->SetPosition({ 0, 50 * 10, 0});
	groundCol->AddComponent(new BoxCollider(groundCol, { 12000, 50 * 4 }));
	//groundCol->AddComponent(new Rigidbody(groundCol, INT_MAX));

	//auto penisBaseCol = gameScene->AddGameObject("PenisBaseCol", "Collider");

}

void GenerateWorld1(const std::unique_ptr<Scene>& gameScene)
{
	SDL_Renderer* renderer = gameScene->GetRenderer();
	worlds.push_back(std::vector<GameObject*>());

	std::vector<std::vector<int>> world1_map = GetMapFromCsv(GetWorld1Csv());

	auto gameBackground = gameScene->AddGameObject("GameBackground", "Background");
	gameBackground->AddComponent(new SpriteRenderer(gameBackground, renderer, GetGameBackground(), {0, 0, 0}, { 0, 0, 12000, 800 }, { 0, 0, 12000, 800 }));

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
	player->GetTransform()->SetPosition( { 560, 315, 0 });

	player->AddComponent(new Rigidbody(player, false, 1, 10));
	player->AddComponent(new BoxCollider(player, { 50, 50 }));

	auto bodyAnim = static_cast<Animator*>(player->AddComponent(new Animator(player, renderer)));
	auto movementComp = static_cast<Movement*>(player->AddComponent(new Movement(player, 30.0f, 0.01f, 5.0f)));

	bodyAnim->AddAnimation(nullptr, GetIdleSpriteSheet(), { 0, 0, 100, 100 }, { 0, 0, 50, 50 }, 2, &IsIdle, 2.0f);
	bodyAnim->AddAnimation(nullptr, GetActionSpriteSheet(), { 0, 0, 100, 100 }, { 0, 0, 50, 50 }, 1, &IsIdleActing, 1.0f);
	bodyAnim->AddAnimation(nullptr, GetRunningSpriteSheet(), { 100, 0, 100, 100 }, { 0, 0, 50, 50 }, 3, &IsRunning, 0.5f);
	bodyAnim->AddAnimation(nullptr, GetActionSpriteSheet(), { 100, 0, 100, 100 }, { 0, 0, 50, 50 }, 3, &IsRunningActing, 0.5f);
	bodyAnim->AddAnimation(nullptr, GetJumpingSpriteSheet(), { 0, 0, 100, 100 }, { 0, 0, 50, 50 }, 2, &IsJumping, 1.0f);
	bodyAnim->AddAnimation(nullptr, GetJumpingSpriteSheet(), { 200, 0, 100, 100 }, { 0, 0, 50, 50 }, 1, &IsJumpingActing, 1.0f);

	player->AddComponent(new Player(player, gameScene.get(), movementComp));
	player->AddComponent(new Gravity(player, 0.01f));

	auto arm = gameScene->AddGameObject("PlayerArm", "Player");
	auto armAnim = static_cast<Animator*>(arm->AddComponent(new Animator(player, renderer)));

	armAnim->AddAnimation(nullptr, GetArmSpriteSheet(), { 112 * IDLE_ARM, 0, 112, 100 }, { 0, 0, 56, 50 }, 1, &IsIdle, 1.0f);
	armAnim->AddAnimation(nullptr, GetArmSpriteSheet(), { 112 * SHOOTING_ARM, 0, 112, 100 }, { 0, 0, 56, 50 }, 1, &IsPlayerShooting, 1.0f);
	armAnim->AddAnimation(nullptr, GetArmSpriteSheet(), { 112 * PUNCHING_ARM, 0, 112, 100 }, { 0, 0, 56, 50 }, 1, &IsPlayerPunching, 1.0f);
	armAnim->AddAnimation(nullptr, GetArmSpriteSheet(), { 112 * INVIS_ARM, 0, 112, 100 }, { 0, 0, 56, 50 }, 1, &IsRunning, 1.0f);
	armAnim->AddAnimation(nullptr, GetArmSpriteSheet(), { 112 * INVIS_ARM, 0, 112, 100 }, { 0, 0, 56, 50 }, 1, &IsJumping, 1.0f);

	arm->AddComponent(new PlayerArm(arm, player));

	auto camera = gameScene->AddGameObject("Camera", "Camera");
	camera->AddComponent(new Camera(camera, player, setCameraPosFunc));
}
