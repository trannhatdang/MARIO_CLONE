#include "CustomScene/GameScene/LocalPlayerIndicator.h"
#include "engine/GameObject.h"

LocalPlayerIndicator::LocalPlayerIndicator(GameObject* obj, GameObject* targetPlayer) 
    : Component("LocalPlayerIndicator", obj), m_targetPlayer(targetPlayer)
{
}

LocalPlayerIndicator::~LocalPlayerIndicator()
{
}

void LocalPlayerIndicator::OnIterate()
{
    // Empty - just for base class compliance
}

void LocalPlayerIndicator::OnDraw(SDL_Renderer* renderer)
{
    if (!m_targetPlayer) return;

    // Position indicator above the target player
    Vector3 targetPos = m_targetPlayer->GetTransform()->GetPosition();
    
    // Draw a green rectangle above the player
    SDL_FRect rect = {
        (float)(targetPos.x),
        (float)(targetPos.y - 20),
        50.0f,
        10.0f
    };

    // Set color and draw filled rectangle
    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderFillRect(renderer, &rect);
    
    // Draw border
    SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);  // Darker green
    SDL_RenderRect(renderer, &rect);
}

std::unique_ptr<Component> LocalPlayerIndicator::copy()
{
    return std::unique_ptr<Component>(new LocalPlayerIndicator(gameObject, m_targetPlayer));
}
