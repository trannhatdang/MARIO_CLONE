#ifndef DESTRUCTIBLE_BLOCK_H_
#define DESTRUCTIBLE_BLOCK_H_

#include "engine/Components/Component.h"
#include "engine/Components/SpriteRenderer.h"
#include "engine/Components/BoxCollider.h"
#include "engine/Scene.h"
#include "Star.h"
#include "SuperPunch.h"
#include "Config.h"
#include "PlayerInventory.h"

class DestructibleBlock : public Component
{
	private:
		Scene* m_scene;
		PlayerInventory* m_inven;
		SDL_Renderer* m_renderer;
		bool m_hasItems = false;
		bool m_star = false;
	public:
		DestructibleBlock(GameObject*, Scene*, SDL_Renderer*, PlayerInventory*, bool, bool);
		~DestructibleBlock();
		void OnIterate();
		void OnCollisionEnter(GameObject* other);
		std::unique_ptr<Component> copy();
};

#endif
