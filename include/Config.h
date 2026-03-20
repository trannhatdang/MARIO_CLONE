#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

int GetWindowWidth();
int GetWindowHeight();
std::string GetBKLogo();
std::string GetBKLogoSpriteSheet();
std::string GetBKLogoIntroVideo();
std::string GetBackgroundSprite();
std::string GetButtonFrameSprite();
std::string GetBackIconFramedSprite();
std::string GetPanelSprite(bool aspect = false);
std::string GetBigPanelSprite(bool aspect = false);
std::string GetWorldImg(int index);
std::string GetSelectorSprite();
std::string GetSaveFile();
std::string GetTilemap();
std::string GetFont();

#endif
