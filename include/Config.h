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
std::string GetRocketSprite();
std::string GetRocket2Sprite();
std::string GetRocket3Sprite();
std::string GetBlocks1Csv();
std::string GetWorld1Csv();
std::string GetIdleSpriteSheet();
std::string GetRunningSpriteSheet();
std::string GetActionSpriteSheet();
std::string GetArmSpriteSheet();
std::string GetFlippedArmSpriteSheet();
std::string GetJumpingSpriteSheet();
std::string GetPlayerBulletSprite();
std::string GetSniperBulletSprite();
std::string GetEnemyWorld1Csv();
std::string GetSniperSpriteSheet();
std::string GetGameBackground();
std::string GetStarSprite();
std::string GetSuperPunchSprite();
std::string GetBossSprite();
std::string GetDestructibleBlockSprite();
std::string GetPushableBlockSprite();
std::string GetBackgroundMusic();
std::string GetHitSFX();
std::string GetFont();

#endif
