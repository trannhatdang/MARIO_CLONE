#include "engine/Components/SpriteRenderer.h"
#include "engine/GameObject.h"

SpriteRenderer::SpriteRenderer(GameObject* gameObject, SDL_Renderer* renderer, const std::string& filepath, Vector3f anchor, SDL_FRect srcrect, SDL_FRect dstrect) : Component("SpriteRenderer", gameObject), m_anchor(anchor), m_srcrect(srcrect), m_dstrect(dstrect), filepath(filepath), m_renderer(renderer)
{
	m_texture = CreateTextureFromPNG(renderer, filepath);
	if(m_anchor.magnitude() > 1)
	{
		m_anchor = {0, 0, 0};
	}
}

SpriteRenderer::~SpriteRenderer() 
{
	SDL_DestroyTexture(m_texture);
}

void SpriteRenderer::OnStart()
{

}

void SpriteRenderer::OnIterate() 
{

}

void SpriteRenderer::OnDraw(SDL_Renderer* renderer)
{
	if(!m_enabled)
	{
		return;
	}

	Vector3 pos = static_cast<Transform*>(this->gameObject->GetTransform())->GetPosition();
	SDL_Rect viewport;
	//god what would happen if we go 3d?
	Vector3 cameraPos = GetCameraPos();

	viewport.x = std::min(std::max(pos.x - cameraPos.x, -10000), 10000);
	viewport.x = viewport.x - m_dstrect.w * m_anchor.x;

	viewport.y = std::min(std::max(pos.y - cameraPos.y, -10000), 10000);
	viewport.y = viewport.y - m_dstrect.h * m_anchor.y;

	viewport.w = m_dstrect.w;
	viewport.h = m_dstrect.h;

	DrawTexture(renderer, m_texture, viewport, m_srcrect, m_dstrect);
}

void SpriteRenderer::OnEvent(SDL_Event* event)
{

}

std::unique_ptr<Component> SpriteRenderer::copy()
{
	return std::make_unique<SpriteRenderer>(gameObject, m_renderer, filepath, m_anchor, m_srcrect, m_dstrect);
}

SDL_FRect SpriteRenderer::GetDstRect() const
{
	return m_dstrect;
}

void SpriteRenderer::SetDstRect(SDL_FRect dstrect)
{
	m_dstrect = dstrect;
}

SDL_Rect SpriteRenderer::GetViewport() const
{
	Vector3 pos = static_cast<Transform*>(this->gameObject->GetTransform())->GetPosition();
	SDL_Rect viewport;
	//god what would happen if we go 3d?
	Vector3 cameraPos = GetCameraPos();

	viewport.x = std::min(std::max(pos.x - cameraPos.x, -10000), 10000);
	viewport.x = viewport.x - m_dstrect.w * m_anchor.x;

	viewport.y = std::min(std::max(pos.y - cameraPos.y, -10000), 10000);
	viewport.y = viewport.y - m_dstrect.h * m_anchor.y;

	viewport.w = m_dstrect.w;
	viewport.h = m_dstrect.h;

	return viewport;
}
