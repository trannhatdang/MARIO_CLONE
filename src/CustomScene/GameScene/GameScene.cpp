#include "CustomScene/GameScene/GameScene.h"

using json = nlohmann::json;

const int SKY_TILE = 0;
const int GRASS_TILE = 1;
const int GROUND_TILE = 2;
const int BLOCK_TILE = 3;
const int DESTRUCTABLE_BLOCK_TILE = 4;
const int FLASHING_BLOCK_TILE = 5;

const int ROCKET_SPAWNER = 1;
const int SNIPER = 2;

const int SHOOTING_ARM = 0;
const int PUNCHING_ARM = 1;
const int IDLE_ARM = 2;
const int INVIS_ARM = 3;

const int TILE_SIZE = 50;

static SDL_FRect tile_dstrect = { 0, 0, TILE_SIZE, TILE_SIZE };

static std::vector<std::vector<GameObject*>> worlds;
static PlayerInventory* playerInvenComp;

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

	return player->IsOnGround() && !player->IsActing() && !player->IsRunning() && !player->IsFacingLeft();
}

bool IsIdleLeft(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return player->IsOnGround() && !player->IsActing() && !player->IsRunning() && player->IsFacingLeft();
}

bool IsIdleActing(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return player->IsOnGround() && player->IsActing() && !player->IsRunning() && !player->IsFacingLeft();
}

bool IsIdleActingLeft(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return player->IsOnGround() && player->IsActing() && !player->IsRunning() && player->IsFacingLeft();
}

bool IsRunning(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return player->IsOnGround() && !player->IsActing() && player->IsRunning() && !player->IsFacingLeft();
}

bool IsRunningLeft(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return player->IsOnGround() && !player->IsActing() && player->IsRunning() && player->IsFacingLeft();
}

bool IsRunningActing(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return player->IsOnGround() && player->IsActing() && player->IsRunning() && !player->IsFacingLeft();
}

bool IsRunningActingLeft(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return player->IsOnGround() && player->IsActing() && player->IsRunning() && player->IsFacingLeft();
}

bool IsJumping(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return !player->IsOnGround() && !player->IsActing() && !player->IsFacingLeft();
}

bool IsJumpingLeft(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return !player->IsOnGround() && !player->IsActing() && player->IsFacingLeft();
}

bool IsJumpingActing(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return !player->IsOnGround() && player->IsActing() && !player->IsFacingLeft();
}

bool IsJumpingActingLeft(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return !player->IsOnGround() && player->IsActing() && player->IsFacingLeft();
}

bool IsPlayerShooting(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return player->IsOnGround() && player->IsShooting() && !player->IsFacingLeft();
}

bool IsPlayerShootingLeft(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return player->IsOnGround() && player->IsShooting() && player->IsFacingLeft();
}

bool IsPlayerPunching(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return player->IsOnGround() && player->IsPunching() && !player->IsFacingLeft();
}

bool IsPlayerPunchingLeft(GameObject* obj)
{
	Player* player = static_cast<Player*>(obj->GetComponent("Player"));

	return player->IsOnGround() && player->IsPunching() && player->IsFacingLeft();
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
						sniper->AddComponent(new Sniper(sniper, gameScene.get(), playerInvenComp));
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

void GenerateColliders1(const std::unique_ptr<Scene>& gameScene, const std::vector<std::vector<int>>& map)
{
	auto groundCol = gameScene->AddGameObject("GroundCollider", "Collider");
	groundCol->GetTransform()->SetPosition({ 0, 50 * 10, 0});
	groundCol->AddComponent(new BoxCollider(groundCol, { 12000, 50 * 4 }));
	//groundCol->AddComponent(new Rigidbody(groundCol, INT_MAX));

	// auto penisBaseCol = gameScene->AddGameObject("PenisBaseCol", "Collider");
	// penisBaseCol->GetTransform()->SetPosition({ 350, 450, 0 });
	// penisBaseCol->AddComponent(new SpriteRenderer(penisBaseCol, gameScene->GetRenderer(), GetTilemap(), { 0, 0, 0 }, { 300, 0, 100, 100 }, { 0, 0, 50, 50 }));
	// penisBaseCol->AddComponent(new BoxCollider(penisBaseCol, { 50, 50 }, false, true));
	
	for(int i = 0; i < map.size(); ++i)
	{
		for(int j = 0; j < map[i].size(); ++j)
		{
			if(map[i][j] <= 2) continue;

			auto col = gameScene->AddGameObject("Collider", "Collider");
			Vector3 pos = { 50 * j, 50 * i, 0 };
			// std::cout << pos << std::endl;
			col->GetTransform()->SetPosition({ 50 * j, 50 * i, 0 });
			col->AddComponent(new BoxCollider(col, { 50, 50 }, false, true));
		}
	}
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

	GenerateColliders1(gameScene, world1_map);
	SpawnEnemy1(gameScene);
	//SpawnBoss1(gameScene);

	//SetActiveWorld1(false);
}

void GenerateGameScene(const std::unique_ptr<Scene>& gameScene, void (*setCameraPosFunc)(Vector3))
{
	SDL_Renderer* renderer = gameScene->GetRenderer();

	auto playerInven = gameScene->AddGameObject("PlayerInventory", "Inventory");
	playerInvenComp = static_cast<PlayerInventory*>(playerInven->AddComponent(new PlayerInventory(playerInven)));
	GenerateWorld1(gameScene);
		
	auto player = gameScene->AddGameObject("Player", "Player");
	player->GetTransform()->SetPosition( { 560, 315, 0 });

	player->AddComponent(new Rigidbody(player, false, 1, 10));
	player->AddComponent(new BoxCollider(player, { 45, 45 }));

	auto bodyAnim = static_cast<Animator*>(player->AddComponent(new Animator(player, renderer)));
	auto movementComp = static_cast<Movement*>(player->AddComponent(new Movement(player, 50.0f, 0.005f, 5.0f)));

	bodyAnim->AddAnimation(nullptr, GetIdleSpriteSheet(), { 0, 0, 100, 100 }, { 0, 0, 50, 50 }, 2, &IsIdle, 1.0f);
	bodyAnim->AddAnimation(nullptr, GetActionSpriteSheet(), { 0, 0, 100, 100 }, { 0, 0, 50, 50 }, 1, &IsIdleActing, 1.0f);
	bodyAnim->AddAnimation(nullptr, GetRunningSpriteSheet(), { 100, 0, 100, 100 }, { 0, 0, 50, 50 }, 3, &IsRunning, 0.05f);
	bodyAnim->AddAnimation(nullptr, GetActionSpriteSheet(), { 100, 0, 100, 100 }, { 0, 0, 50, 50 }, 3, &IsRunningActing, 0.05f);
	bodyAnim->AddAnimation(nullptr, GetJumpingSpriteSheet(), { 0, 0, 100, 100 }, { 0, 0, 50, 50 }, 2, &IsJumping, 1.0f);
	bodyAnim->AddAnimation(nullptr, GetJumpingSpriteSheet(), { 200, 0, 100, 100 }, { 0, 0, 50, 50 }, 1, &IsJumpingActing, 1.0f);

	bodyAnim->AddAnimation(nullptr, GetIdleSpriteSheet(), { 0, 0, 100, 100 }, { 0, 0, 50, 50 }, 2, &IsIdleLeft, 2.0f, SDL_FLIP_HORIZONTAL);
	bodyAnim->AddAnimation(nullptr, GetActionSpriteSheet(), { 0, 0, 100, 100 }, { 0, 0, 50, 50 }, 1, &IsIdleActingLeft, 1.0f, SDL_FLIP_HORIZONTAL);
	bodyAnim->AddAnimation(nullptr, GetRunningSpriteSheet(), { 100, 0, 100, 100 }, { 0, 0, 50, 50 }, 3, &IsRunningLeft, 0.05f, SDL_FLIP_HORIZONTAL);
	bodyAnim->AddAnimation(nullptr, GetActionSpriteSheet(), { 100, 0, 100, 100 }, { 0, 0, 50, 50 }, 3, &IsRunningActingLeft, 0.05f, SDL_FLIP_HORIZONTAL);
	bodyAnim->AddAnimation(nullptr, GetJumpingSpriteSheet(), { 0, 0, 100, 100 }, { 0, 0, 50, 50 }, 2, &IsJumpingLeft, 1.0f, SDL_FLIP_HORIZONTAL);
	bodyAnim->AddAnimation(nullptr, GetJumpingSpriteSheet(), { 200, 0, 100, 100 }, { 0, 0, 50, 50 }, 1, &IsJumpingActingLeft, 1.0f, SDL_FLIP_HORIZONTAL);

	player->AddComponent(new Player(player, gameScene.get(), movementComp, playerInvenComp));
	player->AddComponent(new Gravity(player, 0.05f));

	auto arm = gameScene->AddGameObject("PlayerArm", "Player");
	auto armAnim = static_cast<Animator*>(arm->AddComponent(new Animator(player, renderer)));

	armAnim->AddAnimation(nullptr, GetArmSpriteSheet(), { 112 * IDLE_ARM, 0, 112, 100 }, { 0, 0, 56, 50 }, 1, &IsIdle, 1.0f);
	armAnim->AddAnimation(nullptr, GetArmSpriteSheet(), { 112 * SHOOTING_ARM, 0, 112, 100 }, { 0, 0, 56, 50 }, 1, &IsPlayerShooting, 1.0f);
	armAnim->AddAnimation(nullptr, GetArmSpriteSheet(), { 112 * PUNCHING_ARM, 0, 112, 100 }, { 0, 0, 56, 50 }, 1, &IsPlayerPunching, 1.0f);
	armAnim->AddAnimation(nullptr, GetArmSpriteSheet(), { 112 * INVIS_ARM, 0, 112, 100 }, { 0, 0, 56, 50 }, 1, &IsRunning, 1.0f);
	armAnim->AddAnimation(nullptr, GetArmSpriteSheet(), { 112 * INVIS_ARM, 0, 112, 100 }, { 0, 0, 56, 50 }, 1, &IsJumping, 1.0f);

	armAnim->AddAnimation(nullptr, GetFlippedArmSpriteSheet(), { 112 * IDLE_ARM, 0, 112, 100 }, { 0, 0, 56, 50 }, 1, &IsIdleLeft, 1.0f);
	armAnim->AddAnimation(nullptr, GetFlippedArmSpriteSheet(), { 112 * SHOOTING_ARM, 0, 112, 100 }, { 0, 0, 56, 50 }, 1, &IsPlayerShootingLeft, 1.0f);
	armAnim->AddAnimation(nullptr, GetFlippedArmSpriteSheet(), { 112 * PUNCHING_ARM, 0, 112, 100 }, { 0, 0, 56, 50 }, 1, &IsPlayerPunchingLeft, 1.0f);
	armAnim->AddAnimation(nullptr, GetFlippedArmSpriteSheet(), { 112 * INVIS_ARM, 0, 112, 100 }, { 0, 0, 56, 50 }, 1, &IsRunningLeft, 1.0f);
	armAnim->AddAnimation(nullptr, GetFlippedArmSpriteSheet(), { 112 * INVIS_ARM, 0, 112, 100 }, { 0, 0, 56, 50 }, 1, &IsJumpingLeft, 1.0f);

	arm->AddComponent(new PlayerArm(arm, player));

	auto camera = gameScene->AddGameObject("Camera", "Camera");
	camera->AddComponent(new Camera(camera, player, setCameraPosFunc));
}
