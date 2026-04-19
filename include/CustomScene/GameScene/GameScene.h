#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include <fstream>
#include "engine/Scene.h"
#include "engine/Components/SpriteRenderer.h"
#include "engine/Components/Rigidbody.h"
#include "engine/Components/Tilemap.h"
#include "engine/Components/Animator.h"
#include "engine/Components/BoxCollider.h"
#include "engine/Components/Font.h"
#include "engine/Components/Animator.h"
#include "nlohmann/json.hpp"
#include "Movement.h"
#include "Camera.h"
#include "RocketSpawner.h"
#include "Config.h"
#include "Gravity.h"
#include "Sniper.h"
#include "Player.h"
#include "PlayerArm.h"
#include "PlayerInventory.h"
#include "DestructibleBlock.h"
#include "PunchableBlock.h"
#include "Star.h"
#include "SuperPunch.h"
#include "Boss.h"
#include "Audio.h"
#include "Network.h"
#include "NetworkSync.h"
#include "LocalPlayerIndicator.h"

extern bool isMultiplayer;
extern bool isOnline;
extern bool isServer;
extern std::string clientIP;
extern int clientPort;

void SetWorld(int val);
void GenerateGameScene(const std::unique_ptr<Scene>& gameScene, void (*setCameraPosFunc)(Vector3));
void SpawnRemotePlayer(Scene* gameScene);

#endif
