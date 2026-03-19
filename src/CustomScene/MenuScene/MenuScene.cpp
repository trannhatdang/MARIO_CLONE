#include "CustomScene/MenuScene/MenuScene.h"

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
	background->AddComponent(new SlowMovingBackground(background));
	background->AddComponent(new SpriteRenderer(background, renderer, GetBackgroundSprite(), background_srcrect, background_dstrect));


}
