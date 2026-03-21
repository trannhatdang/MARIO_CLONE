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
#include "nlohmann/json.hpp"
#include "Movement.h"
#include "Camera.h"
#include "RocketSpawner.h"
#include "Config.h"
#include "Gravity.h"

void GenerateGameScene(const std::unique_ptr<Scene>& gameScene, int (*getCurrSaveFunc)(), void (*setCameraPosFunc)(Vector3));

#endif
