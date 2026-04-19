#include <SDL3/SDL.h>
#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <chrono>
#include <memory>
#include "Config.h"
#include "engine/DG_Time.h"
#include "engine/Scene.h"
#include "CustomScene/GameScene/GameScene.h"
#include "CustomScene/MenuScene/MenuScene.h"
#include "CustomScene/IntroScene/IntroScene.h"
#include "CustomScene/GameScene/GameFrameCounter.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

static SDL_Renderer* renderer = nullptr;
static SDL_Window* window = nullptr;
static std::unique_ptr<Scene> scenes[10];
static Scene* currScene;
static std::chrono::milliseconds frametime = std::chrono::milliseconds(16);
static std::chrono::time_point<std::chrono::system_clock> last_iterate_point = std::chrono::system_clock::now();

static Vector3 CameraPos;

bool isMultiplayer = false;
bool isOnline = false;
bool isServer = false;

std::string clientIP = "127.0.0.1";
int clientPort = 12345;

static void SetCameraPos(Vector3 pos)
{
	CameraPos = pos;
}

Vector3 GetCameraPos()
{
	return CameraPos;
}

extern void SetWorld(int);

static bool gameSceneGenerated = false;
static bool lastIsOnline = false;
static bool lastIsMultiplayer = false;
static bool lastIsServer = false;

static void ChangeScene(int index)
{
	if (index == 2) {
		// Regenerate game scene if flags have changed or not yet generated
		if (!gameSceneGenerated || 
		    isOnline != lastIsOnline || 
		    isMultiplayer != lastIsMultiplayer || 
		    isServer != lastIsServer) {
			std::cout << "Regenerating game scene with updated flags" << std::endl;
			GenerateGameScene(scenes[2], &SetCameraPos);
			gameSceneGenerated = true;
			lastIsOnline = isOnline;
			lastIsMultiplayer = isMultiplayer;
			lastIsServer = isServer;
		}
	}
	currScene = scenes[index].get();
	currScene->OnStart();
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char** argv)
{
	srand(time(0));

	char windowCaption[5] = "game";
	SDL_SetAppMetadata("MARIO CLONE", "0.1", "deng_MARIO");

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	
	if(!SDL_CreateWindowAndRenderer(windowCaption, GetWindowWidth(), GetWindowHeight(), SDL_WINDOW_RESIZABLE, &window, &renderer))
	{
		SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if(!TTF_Init())
	{
		SDL_Log("TTF failed to initialize");
		return SDL_APP_FAILURE;
	}

	SDL_SetRenderLogicalPresentation(renderer, GetWindowWidth(), GetWindowHeight(), SDL_LOGICAL_PRESENTATION_LETTERBOX);

	SDL_StartTextInput(window);

	scenes[0] = std::make_unique<Scene>("IntroScene", &ChangeScene, renderer, window);
	scenes[1] = std::make_unique<MenuScene>("MenuScene", &ChangeScene, renderer, window);
	scenes[2] = std::make_unique<Scene>("GameScene", &ChangeScene, renderer, window);

	GenerateIntroScene(scenes[0]);
	// GameScene will be generated when the user starts a game from the menu
	// This allows the online flags to be set before generation

	ChangeScene(1);

	currScene->OnStart();

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
	DGTime_recordDeltaTime();

	if(std::chrono::system_clock::now() - last_iterate_point > frametime)
	{
		currScene->OnFixedIterate();
		last_iterate_point = std::chrono::system_clock::now();
	}
	currScene->OnIterate();
	
	// Increment global frame counter for deterministic enemy sync
	IncrementGameFrameCount();
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	currScene->OnDraw(renderer);
	SDL_RenderPresent(renderer);

	DGTime_stopRecordDeltaTime();

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
	if (event->type == SDL_EVENT_QUIT)
	{
		return SDL_APP_SUCCESS;
	}

	currScene->OnEvent(event);
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
	//TTF_Quit();
}
