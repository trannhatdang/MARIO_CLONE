#include "CustomScene/MenuScene/MenuScene.h"

void OpenStartGamePanel()
{

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
	background->AddComponent(new SpriteRenderer(background, renderer, GetBackgroundSprite(), background_srcrect, background_dstrect));
	background->AddComponent(new SlowMovingBackground(background));

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

	auto startGamePanel = gameScene->AddGameObject("StartGamePanel", "Panel");
	startGamePanel->AddComponent(new SpriteRenderer(startGamePanel, renderer, GetPanelSprite(), panel_srcrect, panel_dstrect));
	auto growBigComp = startGamePanel->AddComponent(new GrowBig(startGamePanel));

	SDL_FRect startbutton_srcrect;
	startbutton_srcrect.x = 0;
	startbutton_srcrect.y = 0;
	startbutton_srcrect.w = 300;
	startbutton_srcrect.h = 100;

	SDL_FRect startbutton_dstrect;
	startbutton_dstrect.x = 0;
	startbutton_dstrect.y = 0;
	startbutton_dstrect.w = 300;
	startbutton_dstrect.h = 100;

	auto startButton = gameScene->AddGameObject("StartButton", "Button");
	startButton->AddComponent(new SpriteRenderer(startButton, renderer, GetButtonFrameSprite(), startbutton_srcrect, startbutton_dstrect));
	startButton->AddComponent(new Button(startButton, &OpenStartGamePanel));
}
