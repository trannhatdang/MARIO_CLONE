#ifndef LOCAL_PLAYER_INDICATOR_H_
#define LOCAL_PLAYER_INDICATOR_H_

#include "engine/Components/Component.h"
#include "engine/Components/Transform.h"
#include <SDL3/SDL.h>

class LocalPlayerIndicator : public Component
{
private:
    GameObject* m_targetPlayer;
    SDL_Color m_color = { 0, 255, 0, 255 };  // Green
    
public:
    LocalPlayerIndicator(GameObject* obj, GameObject* targetPlayer);
    ~LocalPlayerIndicator();
    void OnIterate();  // Required pure virtual method from Component
    void OnDraw(SDL_Renderer* renderer);
    std::unique_ptr<Component> copy();
};

#endif
