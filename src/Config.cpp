#include "Config.h"

const int WINDOW_WIDTH = 1120;
const int WINDOW_HEIGHT = 630;
const std::string BACKGROUND_FILEPATH = ".\\data\\sprites\\background.png";
const std::string BUTTON_FRAME_FILEPATH = ".\\data\\sprites\\buttonframe.png";
const std::string BACK_ICON_FRAMED_FILEPATH = ".\\data\\sprites\\back-icon-framed.png";
const std::string PANEL_FILEPATH = ".\\data\\sprites\\panel.png";
const std::string PANEL169_FILEPATH = ".\\data\\sprites\\panel169.png";
const std::string BIG_PANEL_FILEPATH = ".\\data\\sprites\\big_panel.png";
const std::string BIG_PANEL169_FILEPATH = ".\\data\\sprites\\big_panel169.png";
const std::string RAT_FILEPATH = ".\\data\\sprites\\xdd.png";
const std::string WORLD_IMG_ONE_FILEPATH = ".\\data\\sprites\\world1.png";
const std::string WORLD_IMG_TWO_FILEPATH = ".\\data\\sprites\\world2.png";
const std::string WORLD_IMG_THREE_FILEPATH = ".\\data\\sprites\\world3.png";
const std::string WORLD_IMG_NEW_SAVE_FILEPATH = ".\\data\\sprites\\new_save.png";
const std::string SELECTOR_FILEPATH = ".\\data\\sprites\\selector.png";
const std::string SAVE_FILE_FILEPATH = ".\\data\\save\\save.json";
const std::string TILEMAP_FILEPATH = ".\\data\\sprites\\tilemap.png";
const std::string ROCKET_FILEPATH = ".\\data\\sprites\\rocket.png";
const std::string ROCKET2_FILEPATH = ".\\data\\sprites\\rocket2.png";
const std::string ROCKET3_FILEPATH = ".\\data\\sprites\\rocket3.png";
const std::string WORLD1_CSV_FILEPATH = ".\\data\\world\\world1.csv";
const std::string IDLE_FILEPATH = ".\\data\\sprites\\player_idle.png";
const std::string RUNNING_FILEPATH = ".\\data\\sprites\\player_run.png";
const std::string ACTION_FILEPATH = ".\\data\\sprites\\player_action.png";
const std::string JUMPING_FILEPATH = ".\\data\\sprites\\player_jump.png";
const std::string PLAYER_BULLET_FILEPATH = ".\\data\\sprites\\player_bullet.png";
const std::string ARM_FILEPATH = ".\\data\\sprites\\player_arm.png";
const std::string PLAYER_FILEPATH = ".\\data\\sprites\\player.png";
const std::string ENEMY_WORLD1_CSV_FILEPATH = ".\\data\\world\\enemy1.csv";
const std::string SNIPER_FILEPATH = ".\\data\\sprites\\sniper.png";
const std::string FONT_FILEPATH = ".\\data\\VCR_OSD_MONO.ttf";

int GetWindowWidth(){
	return WINDOW_WIDTH;
}

int GetWindowHeight(){
	return WINDOW_HEIGHT;
}

std::string GetBackgroundSprite()
{
	return BACKGROUND_FILEPATH;
}

std::string GetButtonFrameSprite()
{
	return BUTTON_FRAME_FILEPATH;
}

std::string GetBackIconFramedSprite()
{
	return BACK_ICON_FRAMED_FILEPATH;
}

std::string GetPanelSprite(bool aspect)
{
	if(aspect)
	{
		return PANEL169_FILEPATH;
	}
	else
	{
		return PANEL_FILEPATH;
	}
}

std::string GetBigPanelSprite(bool aspect)
{
	if(aspect)
	{
		return BIG_PANEL169_FILEPATH;
	}
	else
	{
		return BIG_PANEL_FILEPATH;
	}
}

std::string GetWorldImg(int index)
{
	switch(index)
	{
		case 0:
			return WORLD_IMG_ONE_FILEPATH;
			break;
		case 1:
			return WORLD_IMG_TWO_FILEPATH;
			break;
		case 2:
			return WORLD_IMG_THREE_FILEPATH;
			break;
		default:
			return WORLD_IMG_NEW_SAVE_FILEPATH;
	}
}

std::string GetSelectorSprite()
{
	return SELECTOR_FILEPATH;
}

std::string GetSaveFile()
{
	return SAVE_FILE_FILEPATH;
}

std::string GetTilemap()
{
	return TILEMAP_FILEPATH;
}	

std::string GetRocketSprite()
{
	return ROCKET_FILEPATH;
}

std::string GetRocket2Sprite()
{
	return ROCKET2_FILEPATH;
}

std::string GetRocket3Sprite()
{
	return ROCKET3_FILEPATH;
}

std::string GetWorld1Csv()
{
	return WORLD1_CSV_FILEPATH;
}

std::string GetIdleSpriteSheet()
{
	return IDLE_FILEPATH;
}

std::string GetRunningSpriteSheet()
{
	return RUNNING_FILEPATH;
}

std::string GetActionSpriteSheet()
{
	return ACTION_FILEPATH;
}

std::string GetJumpingSpriteSheet()
{
	return JUMPING_FILEPATH;
}

std::string GetPlayerBulletSprite()
{
	return PLAYER_BULLET_FILEPATH;
}

std::string GetArmSpriteSheet()
{
	return ARM_FILEPATH;
}

std::string GetPlayerSpritesheet()
{
	return PLAYER_FILEPATH;
}

std::string GetEnemyWorld1Csv()
{
	return ENEMY_WORLD1_CSV_FILEPATH;
}

std::string GetSniperSpriteSheet()
{
	return SNIPER_FILEPATH;
}

std::string GetFont()
{
	return FONT_FILEPATH;
}
