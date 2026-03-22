#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "dg_engine_std.h"
#include "dg_time.h"

class Animation
{
	friend class Animator;
	private:
		SDL_Texture* m_texture;
		SDL_FRect m_srcrect;
		SDL_FRect m_dstrect;
		std::string m_filepath;

		float m_timeSinceLastAnim = 0.0f;
		float m_delay = 0.05f;
		int m_currFrame = 0;
		int m_num_frames;

		SDL_FlipMode m_flipMode = SDL_FLIP_NONE;
	public:
		Animation(SDL_Renderer* renderer, const std::string& filepath, SDL_FRect srcrect, SDL_FRect dstrect, int num_frames, float delay = 0.05f, SDL_FlipMode flipMode = SDL_FLIP_NONE);
		~Animation();
		void OnDraw(SDL_Renderer* renderer, SDL_Rect viewport);

		std::string GetFilepath() const;
		int GetCurrFrame() const;
		SDL_FRect GetSrcRect() const;
		SDL_FRect GetDstRect() const;
		int GetNumFrames() const;
};

#endif
