#include "CustomScene/MenuScene/MenuScene.h"

using json = nlohmann::json;

GrowBig* startGamePanelGrow;
std::vector<GameObject*> gamePanel;

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

void OpenStartGamePanel()
{
	if(!startGamePanelGrow) return;

	startGamePanelGrow->TurnOn(&EnableStartGamePanelChildren);
}

void EnableStartGamePanelChildren()
{
	std::cout << "enabled" << std::endl;
	int size = gamePanel.size();

	for(int i = 0; i < size; ++i)
	{
		if(gamePanel[i])
		{
			gamePanel[i]->SetActive(true);
		}
	}
}

void GenerateMenuScene(const std::unique_ptr<Scene>& gameScene)
{
	gamePanel.reserve(20);
	//READ SAVEFILE DATA
	std::ifstream f(GetSaveFile());
	json save_data = json::parse(f);

	int world1 = save_data["save1"]["world"];
	std::string name1 = save_data["save1"]["name"];
	std::string playtime1 = save_data["save1"]["playtime"];
	int world2 = save_data["save2"]["world"];
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

	SDL_Renderer* renderer = gameScene->GetRenderer();
	auto background = gameScene->AddGameObject("Background", "Background");
	background->GetTransform()->SetPosition({ -200, -200, 0});
	background->AddComponent(new SpriteRenderer(background, renderer, GetBackgroundSprite(), {0, 0, 0}, background_srcrect, background_dstrect));
	background->AddComponent(new SlowMovingBackground(background));

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

	auto startButton = gameScene->AddGameObject("StartButton", "Button");
	startButton->GetTransform()->SetPosition({ 560, 500, 0 });
	startButton->AddComponent(new SpriteRenderer(startButton, renderer, GetPanelSprite(true), {0.5f, 0.5f, 0.5f}, startbutton_srcrect, startbutton_dstrect));
	startButton->AddComponent(new Button(startButton, &OpenStartGamePanel));

	auto startFont = gameScene->AddGameObject("StartFont", "Font");
	startFont->GetTransform()->SetPosition({ 500, 480, 0});
	startFont->AddComponent(new Font(startFont, renderer, GetFont(), "Start"));

	auto menuSelector = gameScene->AddGameObject("MenuSelector", "Selector");
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

	auto startGamePanel = gameScene->AddGameObject("StartGamePanel", "Panel");
	startGamePanel->GetTransform()->SetPosition({ 560, 400, 0 });
	startGamePanel->AddComponent(new SpriteRenderer(startGamePanel, renderer, GetBigPanelSprite(), {0.5f, 0.5f, 0.5f}, panel_srcrect, panel_dstrect));
	startGamePanelGrow = static_cast<GrowBig*>(startGamePanel->AddComponent(new GrowBig(startGamePanel, enlarged_dstrect)));

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
	auto saveSlot1Panel = gameScene->AddGameObject("SaveSlot1Panel", "Panel");
	saveSlot1Panel->GetTransform()->SetPosition({ 560, 300, 0 });
	saveSlot1Panel->AddComponent(new SpriteRenderer(saveSlot1Panel, renderer, GetBigPanelSprite(), {0.5f, 0.5f, 0.5f}, saveslot_srcrect, saveslot_dstrect));
	saveSlot1Panel->SetActive(false);
	gamePanel.push_back(saveSlot1Panel);

	auto saveWorldImg1 = gameScene->AddGameObject("SaveWorldImg1", "SaveWorldImg");
	saveWorldImg1->GetTransform()->SetPosition({ 320, 300, 0 });
	saveWorldImg1->AddComponent(new SpriteRenderer(saveWorldImg1, renderer, GetWorldImg(world1), {0.5f, 0.5f, 0.5f}, worldimg_srcrect, worldimg_dstrect));
	saveWorldImg1->SetActive(false);
	gamePanel.push_back(saveWorldImg1);

	auto saveName1 = gameScene->AddGameObject("SaveName1", "SaveName");
	saveName1->GetTransform()->SetPosition({ 380, 250, 0});
	auto saveNameFont1 = static_cast<Font*>(saveName1->AddComponent(new Font(saveName1, renderer, GetFont())));
	saveName1->SetActive(false);
	saveNameFont1->SetText(name1);
	gamePanel.push_back(saveName1);

	auto savePlaytime1 = gameScene->AddGameObject("SavePlaytime1", "SavePlaytime");
	savePlaytime1->GetTransform()->SetPosition({ 380, 300, 0});
	auto savePlaytimeFont1 = static_cast<Font*>(savePlaytime1->AddComponent(new Font(savePlaytime1, renderer, GetFont())));
	savePlaytime1->SetActive(false);
	savePlaytimeFont1->SetText(playtime1);
	gamePanel.push_back(savePlaytime1);

	//SAVESLOT2
	auto saveSlot2Panel = gameScene->AddGameObject("SaveSlot2Panel", "Panel");
	saveSlot2Panel->GetTransform()->SetPosition({ 560, 480, 0 });
	saveSlot2Panel->AddComponent(new SpriteRenderer(saveSlot2Panel, renderer, GetBigPanelSprite(), {0.5f, 0.5f, 0.5f}, saveslot_srcrect, saveslot_dstrect));
	saveSlot2Panel->SetActive(false);
	gamePanel.push_back(saveSlot2Panel);

	auto saveWorldImg2 = gameScene->AddGameObject("SaveWorldImg2", "SaveWorldImg");
	saveWorldImg2->GetTransform()->SetPosition({ 320, 480, 0 });
	saveWorldImg2->AddComponent(new SpriteRenderer(saveWorldImg2, renderer, GetWorldImg(world2), {0.5f, 0.5f, 0.5f}, worldimg_srcrect, worldimg_dstrect));
	saveWorldImg2->SetActive(false);
	gamePanel.push_back(saveWorldImg2);

	auto saveName2 = gameScene->AddGameObject("SaveName2", "SaveName");
	saveName2->GetTransform()->SetPosition({ 380, 430, 0});
	auto saveNameFont2 = static_cast<Font*>(saveName2->AddComponent(new Font(saveName2, renderer, GetFont())));
	saveName2->SetActive(false);
	saveNameFont2->SetText(name2);
	gamePanel.push_back(saveName2);

	auto savePlaytime2 = gameScene->AddGameObject("SavePlaytime2", "SavePlaytime");
	savePlaytime2->GetTransform()->SetPosition({ 380, 480, 0});
	auto savePlaytimeFont2 = static_cast<Font*>(savePlaytime2->AddComponent(new Font(savePlaytime2, renderer, GetFont())));
	savePlaytime2->SetActive(false);
	savePlaytimeFont2->SetText(playtime2);
	gamePanel.push_back(savePlaytime2);

	auto saveSelector = gameScene->AddGameObject("MenuSelector", "Selector");
	saveSelector->AddComponent(new SpriteRenderer(saveSelector, renderer, GetSelectorSprite(), { 0, 0, 0 }, selector_srcrect, selector_dstrect));
	saveSelector->AddComponent(new Selector(saveSelector, { saveSlot1Panel, saveSlot2Panel }));
}
