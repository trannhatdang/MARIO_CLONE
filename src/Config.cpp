#include "Config.h"

const int WINDOW_WIDTH = 1120;
const int WINDOW_HEIGHT = 800;
const std::string BK_FILEPATH = ".\\data\\sprites\\01_logobachkhoasang.png";
const std::string BK_SPRITESHEET_FILEPATH = ".\\data\\sprites\\bachkhoaanim.png";
const std::string BK_LOGO_INTRO_VIDEO_FILEPATH = ".\\data\\media\\ratintro.mp4";
const std::string BACKGROUND_FILEPATH = ".\\data\\sprites\\background.png";
const std::string BUTTON_FRAME_FILEPATH = ".\\data\\sprites\\buttonframe.png";
const std::string PANEL_FILEPATH = ".\\data\\sprites\\panel.png";
const std::string WORLD_IMG_ONE_FILEPATH = ".\\data\\sprites\\world1.png";
const std::string WORLD_IMG_TWO_FILEPATH = ".\\data\\sprites\\world2.png";
const std::string WORLD_IMG_THREE_FILEPATH = ".\\data\\sprites\\world3.png";
const std::string WORLD_IMG_NEW_SAVE_FILEPATH = ".\\data\\sprites\\new_save.png";
const std::string SELECTOR_FILEPATH = ".\\data\\sprites\\selector.png";
const std::string PLAYER_FILEPATH = ".\\data\\sprites\\megaman-top.png";
const std::string PLAYER_TOP_RIGHT_FILEPATH = ".\\data\\sprites\\megaman-top-right.png";
const std::string PLAYER_TOP_DOWN_FILEPATH = ".\\data\\sprites\\megaman-top-down.png";
const std::string PLAYER_TOP_LEFT_FILEPATH = ".\\data\\sprites\\megaman-top-left.png";
const std::string PLAYER_TOP_UP_FILEPATH = ".\\data\\sprites\\megaman-top-up.png";
const std::string PLAYER_TWO_FILEPATH = ".\\data\\sprites\\megaman-two-top.png";
const std::string PLAYER_TWO_TOP_RIGHT_FILEPATH = ".\\data\\sprites\\megaman-two-top-right.png";
const std::string PLAYER_TWO_TOP_DOWN_FILEPATH = ".\\data\\sprites\\megaman-two-top-down.png";
const std::string PLAYER_TWO_TOP_LEFT_FILEPATH = ".\\data\\sprites\\megaman-two-top-left.png";
const std::string PLAYER_TWO_TOP_UP_FILEPATH = ".\\data\\sprites\\megaman-two-top-up.png";
const std::string GRASS_FILEPATH = ".\\data\\sprites\\grass-big.png";
const std::string BALL_FILEPATH = ".\\data\\sprites\\ball.png";
const std::string ARROW_SELECTED_FILEPATH = ".\\data\\sprites\\arrow-selected.png";
const std::string ARROW_UNSELECTED_FILEPATH = ".\\data\\sprites\\arrow-unselected.png";
const std::string FONT_FILEPATH = ".\\data\\VCR_OSD_MONO.ttf";

int GetWindowWidth(){
	return WINDOW_WIDTH;
}

int GetWindowHeight(){
	return WINDOW_HEIGHT;
}

std::string GetBKLogo()
{
	return BK_FILEPATH;
}

std::string GetBKLogoSpriteSheet()
{
	return BK_SPRITESHEET_FILEPATH;
}

std::string GetBKLogoIntroVideo()
{
	return BK_LOGO_INTRO_VIDEO_FILEPATH;
}

std::string GetBackgroundSprite()
{
	return BACKGROUND_FILEPATH;
}

std::string GetButtonFrameSprite()
{
	return BUTTON_FRAME_FILEPATH;
}

std::string GetPanelSprite()
{
	return PANEL_FILEPATH;
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

std::string GetPlayerTopdownSprite(int index)
{
	switch(index)
	{
		case 0:
			return PLAYER_TOP_RIGHT_FILEPATH;
			break;
		case 1:
			return PLAYER_TOP_DOWN_FILEPATH;
			break;
		case 2:
			return PLAYER_TOP_LEFT_FILEPATH;
			break;
		case 3:
			return PLAYER_TOP_UP_FILEPATH;
			break;
		default:
			return "";
			break;
	}
}

std::string GetPlayerTwoTopdownSprite(int index)
{
	switch(index)
	{
		case 0:
			return PLAYER_TWO_TOP_RIGHT_FILEPATH;
			break;
		case 1:
			return PLAYER_TWO_TOP_DOWN_FILEPATH;
			break;
		case 2:
			return PLAYER_TWO_TOP_LEFT_FILEPATH;
			break;
		case 3:
			return PLAYER_TWO_TOP_UP_FILEPATH;
			break;
		default:
			return "";
			break;
	}
}
std::string GetPlayerSpriteSheet()
{
	return PLAYER_FILEPATH;
}

std::string GetPlayerTwoSpriteSheet()
{
	return PLAYER_TWO_FILEPATH;
}

std::string GetGrassSpriteSheet()
{
	return GRASS_FILEPATH;
}

std::string GetBallSprite()
{
	return BALL_FILEPATH;
}

std::string GetSelectedArrowSprite()
{
	return ARROW_SELECTED_FILEPATH;
}

std::string GetUnselectedArrowSprite()
{
	return ARROW_UNSELECTED_FILEPATH;
}

std::string GetFont()
{
	return FONT_FILEPATH;
}
