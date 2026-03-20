#include "Config.h"

const int WINDOW_WIDTH = 1120;
const int WINDOW_HEIGHT = 630;
const std::string BACKGROUND_FILEPATH = ".\\data\\sprites\\background.png";
const std::string BUTTON_FRAME_FILEPATH = ".\\data\\sprites\\buttonframe.png";
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

std::string GetFont()
{
	return FONT_FILEPATH;
}
