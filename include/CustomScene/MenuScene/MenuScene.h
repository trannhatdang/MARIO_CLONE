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
#include "CustomScene/GameScene/Audio.h"
#include "Selector.h"
#include "GrowBig.h"
#include "SlowMovingBackground.h"
#include "Config.h"
#include "nlohmann/json.hpp"

extern bool isMultiplayer;
extern bool isOnline;
extern bool isServer;

class MenuScene : public Scene {
public:
    MenuScene(const std::string& name, void (*changeSceneCallback)(int), SDL_Renderer* renderer, SDL_Window* window);
    void OnEvent(SDL_Event* event) override;
    void OnIterate() override;
    static void StartClientInputStatic();
    static void ConfirmClientInputStatic();
    static void CancelClientInputStatic();
private:
    void StartClientInput();
    void ConfirmInput();
    void CancelInput();
    bool inputMode = false;
    bool inputIPActive = true;
    std::string inputIP = "127.0.0.1";
    std::string inputPortStr = "12345";
    bool inputUICreated = false;
public:
    GameObject* ipDisplayFont = nullptr;
    GameObject* portDisplayFont = nullptr;
    GameObject* ipLabelFont = nullptr;
    GameObject* portLabelFont = nullptr;
    GameObject* confirmButton = nullptr;
    GameObject* cancelButton = nullptr;
    static MenuScene* instance;
};

void ChangeToGameSceneSave1();
void ChangeToGameSceneSave2();
void CloseStartGamePanel();
void OpenModePanel();
void OpenStartGamePanel();
void EnableStartGamePanelChildren();
void SetSinglePlayer();
void SetLocalMultiplayer();
void SetOnlineServer();
void SetOnlineClient();
void GenerateMenuScene(Scene* menuScene, void (*setCurrWorldFunc)(int));

#endif
