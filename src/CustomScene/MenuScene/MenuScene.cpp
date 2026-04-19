#include "CustomScene/MenuScene/MenuScene.h"
#include <iostream>

using json = nlohmann::json;

void (*setCurrWorldFunc)(int) = nullptr;
GrowBig* startGamePanelGrow;
Scene* currScene;
std::vector<GameObject*> gamePanel;

static GameObject* singleButtonPtr = nullptr;
static GameObject* singleFontPtr = nullptr;
static GameObject* localButtonPtr = nullptr;
static GameObject* localFontPtr = nullptr;
static GameObject* serverButtonPtr = nullptr;
static GameObject* serverFontPtr = nullptr;
static GameObject* clientButtonPtr = nullptr;
static GameObject* clientFontPtr = nullptr;
static GameObject* confirmFont = nullptr;
static GameObject* cancelFont = nullptr;
extern void SetWorld(int);
MenuScene* MenuScene::instance = nullptr;

MenuScene::MenuScene(const std::string& name, void (*changeSceneCallback)(int), SDL_Renderer* renderer, SDL_Window* window)
    : Scene(name, changeSceneCallback, renderer, window) {
    instance = this;
    GenerateMenuScene(this, &SetWorld);
}

void MenuScene::OnEvent(SDL_Event* event) {
    Scene::OnEvent(event);
    if (inputMode) {
        if (event->type == SDL_EVENT_TEXT_INPUT) {
            if (inputIPActive) {
                inputIP += event->text.text;
            } else {
                inputPortStr += event->text.text;
            }
        } else if (event->type == SDL_EVENT_KEY_DOWN) {
            if (event->key.key == SDLK_BACKSPACE) {
                if (inputIPActive && !inputIP.empty()) inputIP.pop_back();
                else if (!inputIPActive && !inputPortStr.empty()) inputPortStr.pop_back();
            } else if (event->key.key == SDLK_RETURN) {
                if (inputIPActive) {
                    inputIPActive = false;
                } else {
                    ConfirmInput();
                }
            } else if (event->key.key == SDLK_TAB) {
                inputIPActive = !inputIPActive;
            } else if (event->key.key == SDLK_ESCAPE) {
                CancelInput();
            }
        }
    }
}

void MenuScene::OnIterate() {
    Scene::OnIterate();
    if (inputMode) {
        if (ipDisplayFont) {
            auto fontComp = static_cast<Font*>(ipDisplayFont->GetComponent("Font"));
            if (fontComp) fontComp->SetText(inputIP);
        }
        if (portDisplayFont) {
            auto fontComp = static_cast<Font*>(portDisplayFont->GetComponent("Font"));
            if (fontComp) fontComp->SetText(inputPortStr);
        }
    }
}


void MenuScene::StartClientInput() {
    inputMode = true;
    inputIPActive = true;
    inputIP = "";
    inputPortStr = "";

    if (!inputUICreated) {
        SDL_Renderer* renderer = GetRenderer();
        SDL_FRect button_srcrect;
        button_srcrect.x = 0;
        button_srcrect.y = 0;
        button_srcrect.w = 160;
        button_srcrect.h = 90;
        SDL_FRect button_dstrect;
        button_dstrect.x = 0;
        button_dstrect.y = 0;
        button_dstrect.w = 130;  // Button width
        button_dstrect.h = 50;   // Button height

        ipLabelFont = AddGameObject("IPLabel", "Font");
        ipLabelFont->GetTransform()->SetPosition({500, 150, 0});
        ipLabelFont->AddComponent(new Font(ipLabelFont, renderer, GetFont(), "IP:"));

        ipDisplayFont = AddGameObject("IPDisplay", "Font");
        ipDisplayFont->GetTransform()->SetPosition({600, 150, 0});
        ipDisplayFont->AddComponent(new Font(ipDisplayFont, renderer, GetFont(), ""));

        portLabelFont = AddGameObject("PortLabel", "Font");
        portLabelFont->GetTransform()->SetPosition({500, 200, 0});
        portLabelFont->AddComponent(new Font(portLabelFont, renderer, GetFont(), "Port:"));

        portDisplayFont = AddGameObject("PortDisplay", "Font");
        portDisplayFont->GetTransform()->SetPosition({600, 200, 0});
        portDisplayFont->AddComponent(new Font(portDisplayFont, renderer, GetFont(), ""));

        confirmButton = AddGameObject("ConfirmButton", "Button");
        confirmButton->GetTransform()->SetPosition({500, 270, 0});
        confirmButton->AddComponent(new SpriteRenderer(confirmButton, renderer, GetPanelSprite(true), {0.5f, 0.5f, 0.5f}, button_srcrect, button_dstrect));
        confirmButton->AddComponent(new Button(confirmButton, &MenuScene::ConfirmClientInputStatic));

        confirmFont = AddGameObject("ConfirmFont", "Font");
        confirmFont->GetTransform()->SetPosition({450, 260, 0});
        confirmFont->AddComponent(new Font(confirmFont, renderer, GetFont(), "Confirm"));

        cancelButton = AddGameObject("CancelButton", "Button");
        cancelButton->GetTransform()->SetPosition({700, 270, 0});
        cancelButton->AddComponent(new SpriteRenderer(cancelButton, renderer, GetPanelSprite(true), {0.5f, 0.5f, 0.5f}, button_srcrect, button_dstrect));
        cancelButton->AddComponent(new Button(cancelButton, &MenuScene::CancelClientInputStatic));

        cancelFont = AddGameObject("CancelFont", "Font");
        cancelFont->GetTransform()->SetPosition({650, 260, 0});
        cancelFont->AddComponent(new Font(cancelFont, renderer, GetFont(), "Cancel"));

        inputUICreated = true;
    }

    if (ipLabelFont) ipLabelFont->SetActive(true);
    if (ipDisplayFont) ipDisplayFont->SetActive(true);
    if (portLabelFont) portLabelFont->SetActive(true);
    if (portDisplayFont) portDisplayFont->SetActive(true);
    if (confirmButton) confirmButton->SetActive(true);
    if (cancelButton) cancelButton->SetActive(true);
	if (confirmFont) confirmFont->SetActive(true);
	if (cancelFont) cancelFont->SetActive(true);
}

void MenuScene::ConfirmInput() {
    try {
        clientPort = std::stoi(inputPortStr);
        clientIP = inputIP;
        SetOnlineClient();
        CancelInput();
    } catch (...) {
        // invalid, do nothing
    }
}

void MenuScene::CancelInput() {
    inputMode = false;
    inputIP = "";
    inputPortStr = "";
    if (ipLabelFont) ipLabelFont->SetActive(false);
    if (ipDisplayFont) ipDisplayFont->SetActive(false);
    if (portLabelFont) portLabelFont->SetActive(false);
    if (portDisplayFont) portDisplayFont->SetActive(false);
    if (confirmButton) confirmButton->SetActive(false);
    if (cancelButton) cancelButton->SetActive(false);
	if (confirmFont) confirmFont->SetActive(false);
	if (cancelFont) cancelFont->SetActive(false);
}

int world1 = 1, world2 = 1;

void ChangeToGameSceneSave1()
{
	if(setCurrWorldFunc)
	{
		setCurrWorldFunc(world1);
	}

	currScene->ChangeScene(2);
}

void ChangeToGameSceneSave2()
{
	if(setCurrWorldFunc)
	{
		setCurrWorldFunc(world1);
	}

	currScene->ChangeScene(2);
}

void CloseStartGamePanel()
{
	if(!startGamePanelGrow) return;

	int size = gamePanel.size();

	for(int i = 0; i < size; ++i)
	{
		if(gamePanel[i])
		{
			gamePanel[i]->SetActive(false);
		}
	}

	startGamePanelGrow->TurnOff();
}

void OpenModePanel()
{
	if (singleButtonPtr) singleButtonPtr->SetActive(true);
	if (singleFontPtr) singleFontPtr->SetActive(true);
	if (localButtonPtr) localButtonPtr->SetActive(true);
	if (localFontPtr) localFontPtr->SetActive(true);
	if (serverButtonPtr) serverButtonPtr->SetActive(true);
	if (serverFontPtr) serverFontPtr->SetActive(true);
	if (clientButtonPtr) clientButtonPtr->SetActive(true);
	if (clientFontPtr) clientFontPtr->SetActive(true);
}

void OpenStartGamePanel()
{
	if(!startGamePanelGrow) return;

	startGamePanelGrow->TurnOn(&EnableStartGamePanelChildren);
}

void EnableStartGamePanelChildren()
{
	int size = gamePanel.size();

	for(int i = 0; i < size; ++i)
	{
		if(gamePanel[i])
		{
			gamePanel[i]->SetActive(true);
		}
	}
}

void SetSinglePlayer() {
	isMultiplayer = false;
	isOnline = false;
	OpenStartGamePanel();
}

void SetLocalMultiplayer() {
	isMultiplayer = true;
	isOnline = false;
	OpenStartGamePanel();
}

void SetOnlineServer() {
	std::cout << "SetOnlineServer called - Starting game as SERVER" << std::endl;
	isMultiplayer = true;
	isOnline = true;
	isServer = true;
	OpenStartGamePanel();
}

void SetOnlineClient() {
	std::cout << "SetOnlineClient called - Starting game as CLIENT" << std::endl;
	isMultiplayer = true;
	isOnline = true;
	isServer = false;
	OpenStartGamePanel();
}

void GenerateMenuScene(Scene* menuScene, void (*setCurrWorldFunc)(int))
{
	std::cout << "GenerateMenuScene called" << std::endl;
	/*std::vector<std::vector<int>> world1_map = GetMapFromCsv(GetWorld1Csv());
	for(int i = 0; i < world1_map.size(); ++i)
	{
		for(int j = 0; j < world1_map[i].size(); ++j)
		{
			std::cout << world1_map[i][j] << ' ';
		}

		std::cout << '\n';
	}*/

	gamePanel.reserve(20);
	currScene = menuScene;
	//READ SAVEFILE DATA
	std::ifstream f(GetSaveFile());
	json save_data = json::parse(f);

	world1 = save_data["save1"]["world"];
	std::string name1 = save_data["save1"]["name"];
	std::string playtime1 = save_data["save1"]["playtime"];
	world2 = save_data["save2"]["world"];
	std::string name2 = save_data["save2"]["name"];
	std::string playtime2 = save_data["save2"]["playtime"];

	SDL_FRect background_srcrect;
	background_srcrect.x = 0;
	background_srcrect.y = 0;
	background_srcrect.w = 1000;
	background_srcrect.h = 720;

	SDL_FRect background_dstrect;
	background_dstrect.x = 0;
	background_dstrect.y = 0;
	background_dstrect.w = 1920;
	background_dstrect.h = 1080;

	SDL_Renderer* renderer = menuScene->GetRenderer();
	auto background = menuScene->AddGameObject("Background", "Background");
	background->GetTransform()->SetPosition({ -200, -200, 0});
	background->AddComponent(new SpriteRenderer(background, renderer, GetGameBackground(), {0, 0, 0}, background_srcrect, background_dstrect));
	background->AddComponent(new SlowMovingBackground(background));
	Audio* aud = static_cast<Audio*>(background->AddComponent(new Audio(background, GetBackgroundMusic(), 10000)));
	aud->Play();

	//MENU
	//STARTBUTTON
	SDL_FRect startbutton_srcrect;
	startbutton_srcrect.x = 0;
	startbutton_srcrect.y = 0;
	startbutton_srcrect.w = 160;
	startbutton_srcrect.h = 90;

	SDL_FRect startbutton_dstrect;
	startbutton_dstrect.x = 0;
	startbutton_dstrect.y = 0;
	startbutton_dstrect.w = 160;
	startbutton_dstrect.h = 90;

	SDL_FRect selector_srcrect;
	selector_srcrect.x = 0;
	selector_srcrect.y = 0;
	selector_srcrect.w = 40;
	selector_srcrect.h = 40;

	SDL_FRect selector_dstrect;
	selector_dstrect.x = 0;
	selector_dstrect.y = 0;
	selector_dstrect.w = 40;
	selector_dstrect.h = 40;

	auto startButton = menuScene->AddGameObject("StartButton", "Button");
	startButton->GetTransform()->SetPosition({ 360, 500, 0 });
	startButton->AddComponent(new SpriteRenderer(startButton, renderer, GetPanelSprite(true), {0.5f, 0.5f, 0.5f}, startbutton_srcrect, startbutton_dstrect));
	startButton->AddComponent(new Button(startButton, &OpenModePanel));

	auto startFont = menuScene->AddGameObject("StartFont", "Font");
	startFont->GetTransform()->SetPosition({ 300, 480, 0});
	startFont->AddComponent(new Font(startFont, renderer, GetFont(), "Start"));

	auto optionButton = menuScene->AddGameObject("StartButton", "Button");
	optionButton->GetTransform()->SetPosition({ 660, 500, 0 });
	optionButton->AddComponent(new SpriteRenderer(optionButton, renderer, GetPanelSprite(true), {0.5f, 0.5f, 0.5f}, startbutton_srcrect, startbutton_dstrect));

	auto optionFont = menuScene->AddGameObject("optionFont", "Font");
	optionFont->GetTransform()->SetPosition({ 600, 480, 0});
	optionFont->AddComponent(new Font(optionFont, renderer, GetFont(), "Options"));

	// Mode buttons
	auto singleButton = menuScene->AddGameObject("SingleButton", "Button");
	singleButton->GetTransform()->SetPosition({200, 400, 0});
	singleButton->AddComponent(new SpriteRenderer(singleButton, renderer, GetPanelSprite(true), {0.5f, 0.5f, 0.5f}, startbutton_srcrect, startbutton_dstrect));
	singleButton->AddComponent(new Button(singleButton, &SetSinglePlayer));
	auto singleFont = menuScene->AddGameObject("SingleFont", "Font");
	singleFont->GetTransform()->SetPosition({140, 380, 0});
	singleFont->AddComponent(new Font(singleFont, renderer, GetFont(), "Single"));
	singleButton->SetActive(false);
	singleFont->SetActive(false);
	singleButtonPtr = singleButton;
	singleFontPtr = singleFont;

	auto localButton = menuScene->AddGameObject("LocalButton", "Button");
	localButton->GetTransform()->SetPosition({400, 400, 0});
	localButton->AddComponent(new SpriteRenderer(localButton, renderer, GetPanelSprite(true), {0.5f, 0.5f, 0.5f}, startbutton_srcrect, startbutton_dstrect));
	localButton->AddComponent(new Button(localButton, &SetLocalMultiplayer));
	auto localFont = menuScene->AddGameObject("LocalFont", "Font");
	localFont->GetTransform()->SetPosition({340, 380, 0});
	localFont->AddComponent(new Font(localFont, renderer, GetFont(), "Local"));
	localButton->SetActive(false);
	localFont->SetActive(false);
	localButtonPtr = localButton;
	localFontPtr = localFont;

	auto serverButton = menuScene->AddGameObject("ServerButton", "Button");
	serverButton->GetTransform()->SetPosition({600, 400, 0});
	serverButton->AddComponent(new SpriteRenderer(serverButton, renderer, GetPanelSprite(true), {0.5f, 0.5f, 0.5f}, startbutton_srcrect, startbutton_dstrect));
	serverButton->AddComponent(new Button(serverButton, &SetOnlineServer));
	auto serverFont = menuScene->AddGameObject("ServerFont", "Font");
	serverFont->GetTransform()->SetPosition({540, 380, 0});
	serverFont->AddComponent(new Font(serverFont, renderer, GetFont(), "Server"));
	serverButton->SetActive(false);
	serverFont->SetActive(false);
	serverButtonPtr = serverButton;
	serverFontPtr = serverFont;

	auto clientButton = menuScene->AddGameObject("ClientButton", "Button");
	clientButton->GetTransform()->SetPosition({800, 400, 0});
	clientButton->AddComponent(new SpriteRenderer(clientButton, renderer, GetPanelSprite(true), {0.5f, 0.5f, 0.5f}, startbutton_srcrect, startbutton_dstrect));
	clientButton->AddComponent(new Button(clientButton, &MenuScene::StartClientInputStatic));
	auto clientFont = menuScene->AddGameObject("ClientFont", "Font");
	clientFont->GetTransform()->SetPosition({740, 380, 0});
	clientFont->AddComponent(new Font(clientFont, renderer, GetFont(), "Client"));
	clientButton->SetActive(false);
	clientFont->SetActive(false);
	clientButtonPtr = clientButton;
	clientFontPtr = clientFont;

	auto menuSelector = menuScene->AddGameObject("MenuSelector", "Selector");
	menuSelector->AddComponent(new SpriteRenderer(menuSelector, renderer, GetSelectorSprite(), { 0, 0, 0 }, selector_srcrect, selector_dstrect));
	menuSelector->AddComponent(new Selector(menuSelector, { startButton }));

	//PANELS
	//START GAME
	SDL_FRect panel_srcrect;
	panel_srcrect.x = 0;
	panel_srcrect.y = 0;
	panel_srcrect.w = 800;
	panel_srcrect.h = 800;

	SDL_FRect panel_dstrect;
	panel_dstrect.x = 0;
	panel_dstrect.y = 0;
	panel_dstrect.w = 800;
	panel_dstrect.h = 450;

	SDL_FRect enlarged_dstrect;
	enlarged_dstrect.x = 0;
	enlarged_dstrect.y = 0;
	enlarged_dstrect.w = 800;
	enlarged_dstrect.h = 450;

	auto startGamePanel = menuScene->AddGameObject("StartGamePanel", "Panel");
	startGamePanel->GetTransform()->SetPosition({ 560, 400, 0 });
	startGamePanel->AddComponent(new SpriteRenderer(startGamePanel, renderer, GetBigPanelSprite(), {0.5f, 0.5f, 0.5f}, panel_srcrect, panel_dstrect));
	startGamePanelGrow = static_cast<GrowBig*>(startGamePanel->AddComponent(new GrowBig(startGamePanel, enlarged_dstrect, 0.001f)));

	SDL_FRect backicon_srcrect;
	backicon_srcrect.x = 0;
	backicon_srcrect.y = 0;
	backicon_srcrect.w = 92;
	backicon_srcrect.h = 92;

	SDL_FRect backicon_dstrect;
	backicon_dstrect.x = 0;
	backicon_dstrect.y = 0;
	backicon_dstrect.w = 40;
	backicon_dstrect.h = 40;

	auto backBtn = menuScene->AddGameObject("BackBtn", "Button");
	backBtn->GetTransform()->SetPosition({ 160, 200, 0});
	backBtn->AddComponent(new SpriteRenderer(backBtn, renderer, GetBackIconFramedSprite(), { 0.5f, 0.5f, 0.5f }, backicon_srcrect, backicon_dstrect));
	backBtn->AddComponent(new Button(backBtn, &CloseStartGamePanel));
	backBtn->SetActive(false);
	gamePanel.push_back(backBtn);

	SDL_FRect saveslot_srcrect;
	saveslot_srcrect.x = 0;
	saveslot_srcrect.y = 0;
	saveslot_srcrect.w = 800;
	saveslot_srcrect.h = 800;

	SDL_FRect saveslot_dstrect;
	saveslot_dstrect.x = 0;
	saveslot_dstrect.y = 0;
	saveslot_dstrect.w = 640;
	saveslot_dstrect.h = 150;

	SDL_FRect worldimg_srcrect;
	worldimg_srcrect.x = 0;
	worldimg_srcrect.y = 0;
	worldimg_srcrect.w = 100;
	worldimg_srcrect.h = 100;

	SDL_FRect worldimg_dstrect;
	worldimg_dstrect.x = 0;
	worldimg_dstrect.y = 0;
	worldimg_dstrect.w = 100;
	worldimg_dstrect.h = 100;

	//SAVESLOT1
	auto saveSlot1Panel = menuScene->AddGameObject("SaveSlot1Panel", "Panel");
	saveSlot1Panel->GetTransform()->SetPosition({ 560, 300, 0 });
	saveSlot1Panel->AddComponent(new SpriteRenderer(saveSlot1Panel, renderer, GetBigPanelSprite(), {0.5f, 0.5f, 0.5f}, saveslot_srcrect, saveslot_dstrect));
	saveSlot1Panel->SetActive(false);
	saveSlot1Panel->AddComponent(new Button(saveSlot1Panel, &ChangeToGameSceneSave1));
	gamePanel.push_back(saveSlot1Panel);

	auto saveWorldImg1 = menuScene->AddGameObject("SaveWorldImg1", "SaveWorldImg");
	saveWorldImg1->GetTransform()->SetPosition({ 320, 300, 0 });
	saveWorldImg1->AddComponent(new SpriteRenderer(saveWorldImg1, renderer, GetWorldImg(world1), {0.5f, 0.5f, 0.5f}, worldimg_srcrect, worldimg_dstrect));
	saveWorldImg1->SetActive(false);
	gamePanel.push_back(saveWorldImg1);

	auto saveName1 = menuScene->AddGameObject("SaveName1", "SaveName");
	saveName1->GetTransform()->SetPosition({ 380, 250, 0});
	auto saveNameFont1 = static_cast<Font*>(saveName1->AddComponent(new Font(saveName1, renderer, GetFont())));
	saveName1->SetActive(false);
	saveNameFont1->SetText(name1);
	gamePanel.push_back(saveName1);

	auto savePlaytime1 = menuScene->AddGameObject("SavePlaytime1", "SavePlaytime");
	savePlaytime1->GetTransform()->SetPosition({ 380, 300, 0});
	auto savePlaytimeFont1 = static_cast<Font*>(savePlaytime1->AddComponent(new Font(savePlaytime1, renderer, GetFont())));
	savePlaytime1->SetActive(false);
	savePlaytimeFont1->SetText(playtime1);
	gamePanel.push_back(savePlaytime1);

	//SAVESLOT2
	auto saveSlot2Panel = menuScene->AddGameObject("SaveSlot2Panel", "Panel");
	saveSlot2Panel->GetTransform()->SetPosition({ 560, 480, 0 });
	saveSlot2Panel->AddComponent(new SpriteRenderer(saveSlot2Panel, renderer, GetBigPanelSprite(), {0.5f, 0.5f, 0.5f}, saveslot_srcrect, saveslot_dstrect));
	saveSlot2Panel->SetActive(false);
	saveSlot2Panel->AddComponent(new Button(saveSlot2Panel, &ChangeToGameSceneSave2));
	gamePanel.push_back(saveSlot2Panel);

	auto saveWorldImg2 = menuScene->AddGameObject("SaveWorldImg2", "SaveWorldImg");
	saveWorldImg2->GetTransform()->SetPosition({ 320, 480, 0 });
	saveWorldImg2->AddComponent(new SpriteRenderer(saveWorldImg2, renderer, GetWorldImg(world2), {0.5f, 0.5f, 0.5f}, worldimg_srcrect, worldimg_dstrect));
	saveWorldImg2->SetActive(false);
	gamePanel.push_back(saveWorldImg2);

	auto saveName2 = menuScene->AddGameObject("SaveName2", "SaveName");
	saveName2->GetTransform()->SetPosition({ 380, 430, 0});
	auto saveNameFont2 = static_cast<Font*>(saveName2->AddComponent(new Font(saveName2, renderer, GetFont())));
	saveName2->SetActive(false);
	saveNameFont2->SetText(name2);
	gamePanel.push_back(saveName2);

	auto savePlaytime2 = menuScene->AddGameObject("SavePlaytime2", "SavePlaytime");
	savePlaytime2->GetTransform()->SetPosition({ 380, 480, 0});
	auto savePlaytimeFont2 = static_cast<Font*>(savePlaytime2->AddComponent(new Font(savePlaytime2, renderer, GetFont())));
	savePlaytime2->SetActive(false);
	savePlaytimeFont2->SetText(playtime2);
	gamePanel.push_back(savePlaytime2);

	auto saveSelector = menuScene->AddGameObject("MenuSelector", "Selector");
	saveSelector->AddComponent(new SpriteRenderer(saveSelector, renderer, GetSelectorSprite(), { 0, 0, 0 }, selector_srcrect, selector_dstrect));
	saveSelector->AddComponent(new Selector(saveSelector, { saveSlot1Panel, saveSlot2Panel }));
}

void MenuScene::StartClientInputStatic() {
    if (instance) instance->StartClientInput();
}

void MenuScene::ConfirmClientInputStatic() {
    if (instance) instance->ConfirmInput();
}

void MenuScene::CancelClientInputStatic() {
    if (instance) instance->CancelInput();
}
