#include "CustomScene/IntroScene/IntroScene.h"

void GenerateIntroScene(const std::unique_ptr<Scene>& gameScene)
{
	SDL_Renderer* renderer = gameScene->GetRenderer();
	auto intro_logo = gameScene->AddGameObject("IntroLogo", "Logo");
	intro_logo->AddComponent(new VideoPlayer(intro_logo, renderer, GetBKLogoIntroVideo(), 800, 600));
}
