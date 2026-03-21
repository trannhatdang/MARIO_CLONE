#ifndef DG_ENGINE_STD_
#define DG_ENGINE_STD_

#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <SDL3/SDL.h>
#include "dg_vector.h"

const int ON_COLLISION_ENTER_EVENT = SDL_RegisterEvents(1);
const int BOX_POS_EVENT = SDL_RegisterEvents(1);

SDL_Texture* CreateTextureFromPNG(SDL_Renderer* renderer, const std::string& filepath);
void DrawTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect viewport, SDL_FRect srcrect, SDL_FRect dstrect);
bool IsPointInsideRect(const Vector3& vec, const SDL_FRect& rect);
bool IsPointInsideRect(const Vector3& vec, const SDL_Rect& rect);
bool CompareRect(const SDL_FRect& lhs, const SDL_FRect& rhs);
SDL_FRect MultRect(const SDL_FRect& rect, float mult);
std::vector<std::vector<int>> GetMapFromCsv(const std::string& filepath);
std::vector<Vector3> GetPosFromCsv(const std::string& filepath);

#endif
