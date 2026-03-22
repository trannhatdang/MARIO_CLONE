#include "engine/Animation.h"

Animation::Animation(SDL_Renderer* renderer, const std::string& filepath, SDL_FRect srcrect, SDL_FRect dstrect, int num_frames, float delay) : m_srcrect(srcrect), m_dstrect(dstrect), m_filepath(filepath), m_delay(delay), m_num_frames(num_frames)
{
	m_texture = CreateTextureFromPNG(renderer, filepath);
	m_currFrame = 0;
	m_timeSinceLastAnim = 0.0f;
}

Animation::~Animation()
{
	SDL_DestroyTexture(m_texture);
}

void Animation::OnDraw(SDL_Renderer* renderer, SDL_Rect viewport)
{
	if(m_timeSinceLastAnim < m_delay)
	{
		return;
	};

	m_timeSinceLastAnim = 0.0f;
	m_currFrame = (m_currFrame + 1) % m_num_frames;

	SDL_FRect srcrect;
	srcrect.x = (float)(m_currFrame * m_srcrect.x);
	srcrect.y = (float(m_srcrect.y));
	srcrect.w = (float)m_srcrect.w;
	srcrect.h = (float)m_srcrect.h;

	DrawTexture(renderer, m_texture, viewport, srcrect, m_dstrect);
}

std::string Animation::GetFilepath() const
{
	return m_filepath;
}

int Animation::GetCurrFrame() const
{
	return m_currFrame;
}

SDL_FRect Animation::GetSrcRect() const
{
	return m_srcrect;
}

SDL_FRect Animation::GetDstRect() const
{
	return m_dstrect;
}

int Animation::GetNumFrames() const
{
	return m_num_frames;
}
