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
	std::ifstream f("save.json");
	json save_data = json::parse(f);

	int world1 = save_data["save1"]["world"];
	std::string name1 = save_data["save1"]["name"];
	std::string playtime1 = save_data["save1"]["playtime"];
	int world2 = save_data["save2"]["world"];
	std::string name2 = save_data["save2"]["name"];
	std::string playtime2 = save_data["save2"]["playtime"];
	int world3 = save_data["save3"]["world"];
	std::string name3 = save_data["save3"]["name"];
	std::string playtime3 = save_data["save3"]["playtime"];

	SDL_FRect background_srcrect;
	background_srcrect.x = 0;
	background_srcrect.y = 0;
	background_srcrect.w = 1920;
	background_srcrect.h = 1080;

	SDL_FRect background_dstrect;
	background_dstrect.x = -200;
	background_dstrect.y = -200;
	background_dstrect.w = 1920 + 200;
	background_dstrect.h = 1080 + 200;

	SDL_Renderer* renderer = gameScene->GetRenderer();
	auto background = gameScene->AddGameObject("Background", "Background");
	background->AddComponent(new SpriteRenderer(background, renderer, GetBackgroundSprite(), {0, 0, 0}, background_srcrect, background_dstrect));
	background->AddComponent(new SlowMovingBackground(background));

	//PANELS
	//START GAME
	SDL_FRect panel_srcrect;
	panel_srcrect.x = 0;
	panel_srcrect.y = 0;
	panel_srcrect.w = 640;
	panel_srcrect.h = 360;

	SDL_FRect panel_dstrect;
	panel_dstrect.x = 0;
	panel_dstrect.y = 0;
	panel_dstrect.w = 640;
	panel_dstrect.h = 360;

	SDL_FRect enlarged_dstrect;
	enlarged_dstrect.x = 0;
	enlarged_dstrect.y = 0;
	enlarged_dstrect.w = 800;
	enlarged_dstrect.h = 450;

	auto startGamePanel = gameScene->AddGameObject("StartGamePanel", "Panel");
	startGamePanel->GetTransform()->SetPosition({ 560, 400, 0 });
	startGamePanel->AddComponent(new SpriteRenderer(startGamePanel, renderer, GetPanelSprite(), {0.5f, 0.5f, 0.5f}, panel_srcrect, panel_dstrect));
	startGamePanelGrow = static_cast<GrowBig*>(startGamePanel->AddComponent(new GrowBig(startGamePanel, enlarged_dstrect)));

	SDL_FRect saveslot_srcrect;
	saveslot_srcrect.x = 0;
	saveslot_srcrect.y = 0;
	saveslot_srcrect.w = 800;
	saveslot_srcrect.h = 450;

	SDL_FRect saveslot_dstrect;
	saveslot_dstrect.x = 0;
	saveslot_dstrect.y = 0;
	saveslot_dstrect.w = 640;
	saveslot_dstrect.h = 120;

	auto saveSlot1Panel = gameScene->AddGameObject("SaveSlot1Panel", "Panel");
	saveSlot1Panel->GetTransform()->SetPosition({ 560, 250, 0 });
	saveSlot1Panel->AddComponent(new SpriteRenderer(saveSlot1Panel, renderer, GetPanelSprite(), {0.5f, 0.5f, 0.5f}, saveslot_srcrect, saveslot_dstrect));
	saveSlot1Panel->SetActive(false);
	gamePanel.push_back(saveSlot1Panel);

	auto saveWorldImg1 = gameScene->AddGameObject("SaveWorldImg1", "SaveWorldImg");
	saveWorldImg1->GetTransform()->SetPosition({ 300, 250, 0 });
	saveWorldImg1->AddComponent(new SpriteRenderer(saveWorldImg1, renderer, GetWorldImg(world1), {0.5f, 0.5f, 0.5f}, saveslot_srcrect, saveslot_dstrect));
	saveWorldImg1->SetActive(false);
	gamePanel.push_back(saveWorldImg1);

	auto saveName1 = gameScene->AddGameObject("SaveName1", "SaveName");
	saveName1->GetTransform()->SetPosition({ 360, 200, 0});
	auto saveNameFont1 = static_cast<Font*>(saveName1->AddComponent(new Font(saveName1, renderer, GetFont())));
	saveNameFont1->SetText(name1);

	auto savePlaytime1 = gameScene->AddGameObject("SavePlaytime1", "SavePlaytime");
	savePlaytime1->GetTransform()->SetPosition({ 360, 250, 0});
	auto savePlaytimeFont1 = static_cast<Font*>(savePlaytime1->AddComponent(new Font(savePlaytime1, renderer, GetFont())));
	savePlaytimeFont1->SetText(playtime1);

	auto saveSlot2Panel = gameScene->AddGameObject("SaveSlot2Panel", "Panel");
	saveSlot2Panel->GetTransform()->SetPosition({ 560, 400, 0 });
	saveSlot2Panel->AddComponent(new SpriteRenderer(saveSlot2Panel, renderer, GetPanelSprite(), {0.5f, 0.5f, 0.5f}, saveslot_srcrect, saveslot_dstrect));
	saveSlot2Panel->SetActive(false);
	gamePanel.push_back(saveSlot2Panel);

	auto saveWorldImg2 = gameScene->AddGameObject("SaveWorldImg2", "SaveWorldImg");
	saveWorldImg2->GetTransform()->SetPosition({ 300, 400, 0 });
	saveWorldImg2->AddComponent(new SpriteRenderer(saveWorldImg2, renderer, GetWorldImg(world2), {0.5f, 0.5f, 0.5f}, saveslot_srcrect, saveslot_dstrect));
	saveWorldImg2->SetActive(false);
	gamePanel.push_back(saveWorldImg2);

	auto saveName2 = gameScene->AddGameObject("SaveName2", "SaveName");
	saveName2->GetTransform()->SetPosition({ 360, 350, 0});
	auto saveNameFont2 = static_cast<Font*>(saveName2->AddComponent(new Font(saveName2, renderer, GetFont())));
	saveNameFont2->SetText(name2);

	auto savePlaytime2 = gameScene->AddGameObject("SavePlaytime2", "SavePlaytime");
	savePlaytime2->GetTransform()->SetPosition({ 360, 400, 0});
	auto savePlaytimeFont2 = static_cast<Font*>(savePlaytime2->AddComponent(new Font(savePlaytime2, renderer, GetFont())));
	savePlaytimeFont2->SetText(playtime2);

	auto saveSlot3Panel = gameScene->AddGameObject("SaveSlot3Panel", "Panel");
	saveSlot3Panel->GetTransform()->SetPosition({ 560, 750, 0 });
	saveSlot3Panel->AddComponent(new SpriteRenderer(saveSlot3Panel, renderer, GetPanelSprite(), {0.5f, 0.5f, 0.5f}, saveslot_srcrect, saveslot_dstrect));
	saveSlot3Panel->SetActive(false);
	gamePanel.push_back(saveSlot3Panel);

	auto saveWorldImg3 = gameScene->AddGameObject("SaveWorldImg3", "SaveWorldImg");
	saveWorldImg3->GetTransform()->SetPosition({ 300, 750, 0 });
	saveWorldImg3->AddComponent(new SpriteRenderer(saveWorldImg3, renderer, GetWorldImg(world3), {0.5f, 0.5f, 0.5f}, saveslot_srcrect, saveslot_dstrect));
	saveWorldImg3->SetActive(false);
	gamePanel.push_back(saveWorldImg3);

	auto saveName3 = gameScene->AddGameObject("SaveName3", "SaveName");
	saveName3->GetTransform()->SetPosition({ 360, 700, 0});
	auto saveNameFont3 = static_cast<Font*>(saveName3->AddComponent(new Font(saveName3, renderer, GetFont())));
	saveNameFont3->SetText(name3);

	auto savePlaytime3 = gameScene->AddGameObject("SavePlaytime3", "SavePlaytime");
	savePlaytime3->GetTransform()->SetPosition({ 360, 750, 0});
	auto savePlaytimeFont3 = static_cast<Font*>(savePlaytime3->AddComponent(new Font(savePlaytime3, renderer, GetFont())));
	savePlaytimeFont3->SetText(playtime3);

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

	auto startButton = gameScene->AddGameObject("StartButton", "Button");
	startButton->GetTransform()->SetPosition({ 560, 500, 0 });
	startButton->AddComponent(new SpriteRenderer(startButton, renderer, GetButtonFrameSprite(), {0.5f, 0.5f, 0.5f}, startbutton_srcrect, startbutton_dstrect));
	startButton->AddComponent(new Button(startButton, &OpenStartGamePanel));
}
