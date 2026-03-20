#include "CustomScene/MenuScene/MenuScene.h"

GrowBig* startGamePanelGrow;
GameObject* gamePanel[10];

void CloseStartGamePanel()
{
	if(!startGamePanelGrow) return;

	for(int i = 0; i < 10; ++i)
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
	for(int i = 0; i < 10; ++i)
	{
		if(gamePanel[i])
		{
			gamePanel[i]->SetActive(true);
		}
	}
}

void GenerateMenuScene(const std::unique_ptr<Scene>& gameScene)
{
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
	saveslot_dstrect.w = 800;
	saveslot_dstrect.h = 450;

	auto saveSlot1 = gameScene->AddGameObject("SaveSlot1Panel", "Panel");
	startGamePanel->GetTransform()->SetPosition({ 560, 400, 0 });
	saveSlot1->AddComponent(new SpriteRenderer(saveSlot1, renderer, GetPanelSprite(), {0.5f, 0.5f, 0.5f}, saveslot_srcrect, saveslot_dstrect));
	saveSlot1->SetActive(false);

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
