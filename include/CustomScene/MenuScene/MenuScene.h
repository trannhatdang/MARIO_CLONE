#ifndef MENU_SCENE_H_
#define MENU_SCENE_H_

#include <fstream>
#include "engine/scene.h"
#include "engine/Components/SpriteRenderer.h"
#include "engine/Components/Rigidbody.h"
#include "engine/Components/Tilemap.h"
#include "engine/Components/Animator.h"
#include "engine/Components/BoxCollider.h"
#include "engine/Components/Font.h"
#include "engine/Components/UI/Button.h"
#include "GrowBig.h"
#include "SlowMovingBackground.h"
#include "Config.h"
#include "nlohmann/json.hpp"

void CloseStartGamePanel();
void OpenStartGamePanel();
void EnableStartGamePanelChildren();
void GenerateMenuScene(const std::unique_ptr<Scene>& gameScene);

#endif
