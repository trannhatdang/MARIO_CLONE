#include "engine/dg_engine_std.h"

SDL_Texture* CreateTextureFromPNG(SDL_Renderer* renderer, const std::string& filepath)
{
	SDL_Surface* surface = SDL_LoadPNG(filepath.c_str());
	if(!surface)
	{
		SDL_Log("Could not create surface for texture creation: %s", SDL_GetError());
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if(!texture)
	{
		SDL_Log("Could not create texture: %s", SDL_GetError());
	}
	SDL_DestroySurface(surface);

	return texture;
}

void DrawTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect viewport, SDL_FRect srcrect, SDL_FRect dstrect)
{
	SDL_SetRenderViewport(renderer, &viewport);
	SDL_RenderTexture(renderer, texture, &srcrect, &dstrect);
	SDL_SetRenderViewport(renderer, NULL);
}

bool IsPointInsideRect(const Vector3& vec, const SDL_FRect& rect)
{
	return vec.x >= rect.x && vec.y >= rect.y && vec.x <= (rect.x + rect.w) && vec.y <= (rect.y + rect.h);
}

bool IsPointInsideRect(const Vector3& vec, const SDL_Rect& rect)
{
	return vec.x >= rect.x && vec.y >= rect.y && vec.x <= (rect.x + rect.w) && vec.y <= (rect.y + rect.h);
}

bool CompareRect(const SDL_FRect& lhs, const SDL_FRect& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.w == rhs.w && lhs.h == rhs.h;
}

SDL_FRect MultRect(const SDL_FRect& rect, float mult)
{
	SDL_FRect new_rect = rect;
	new_rect.x *= mult;
	new_rect.y *= mult;
	new_rect.w *= mult;
	new_rect.h *= mult;

	return new_rect;
}

std::vector<std::vector<int>> GetMapFromCsv(const std::string& filepath)
{
	std::vector<std::vector<int>> ans;

	std::fstream f(filepath);
	std::string line;

	while(std::getline(f, line))
	{
		std::stringstream lineStream(line);
		std::string cell;
		std::vector<int> vec;

		while(std::getline(lineStream, cell, ','))
		{
			int x = 0;
			if (cell.size() > 0)
			{
				x = std::stoi(cell);
			}
			vec.push_back(x);
		}
		ans.push_back(vec);
	}

	return ans;
}
