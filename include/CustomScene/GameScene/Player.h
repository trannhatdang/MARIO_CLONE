#ifndef PLAYER_H_
#define PLAYER_H_

#include "engine/Scene.h"
#include "engine/Components/Component.h"
#include "engine/Components/Rigidbody.h"
#include "engine/Components/Animator.h"
#include "engine/Components/SpriteRenderer.h"
#include "Movement.h"
#include "PlayerBullet.h"
#include "PlayerInventory.h"
#include "PlayerPunch.h"
#include "Config.h"

extern bool isOnline;  // Check if in online mode

class Player : public Component
{
	private:
		Scene* m_scene;
		Movement* m_movement;
		PlayerInventory* m_inven;
		bool m_isLocal = true;  // Track if this is the local player

		float m_actDelay = 0.05f;
		float m_timeSinceLastAct = 0.0f;
		bool m_isShooting = false;
		bool m_isPunching = false;
		bool m_isRunning = false;
		bool m_isOnGround = false;
		int m_shootCounter = 0;  // Incremented when shooting for network sync
		int m_blockDestroyCounter = 0;  // Incremented when block destroyed
		int m_lastDestroyType = 0;  // Type of last destroyed item (1=star, 2=superpunch)
		Vector3 m_lastDestroyPos;  // Position of last destroyed item

		void shoot();
		void punch();
	public:
		Player(GameObject* obj, Scene*, Movement*, PlayerInventory*, float m_shootingDelay = 0.1f);
		~Player();
		void OnIterate();
		void OnEvent(SDL_Event* event);
		void OnCollisionEnter(GameObject* other);
		void OnTriggerEnter(GameObject* other);
		std::unique_ptr<Component> copy();

		bool IsFacingLeft() const;
		bool IsOnGround() const;
		bool IsRunning() const;
		bool IsShooting() const;
		bool IsPunching() const;
		bool IsActing() const;

		void SetFacingLeft(bool value);
		void SetOnGround(bool value);
		void SetRunning(bool value);
		void SetShooting(bool value);
		void SetPunching(bool value);
		void SetActing(bool value);

		bool IsLocal() const { return m_isLocal; }
		void SetLocal(bool local) { m_isLocal = local; }
		
		int GetShootCounter() const { return m_shootCounter; }
		void CreateBulletFromNetwork();  // Called by NetworkSync when player shoots remotely
		
		int GetBlockDestroyCounter() const { return m_blockDestroyCounter; }
		int GetBlockDestroyType() const { return m_lastDestroyType; }
		Vector3 GetBlockDestroyPos() const { return m_lastDestroyPos; }
		void OnBlockDestroyed(int itemType, Vector3 pos);  // Called when block is destroyed
		Scene* GetScene() const { return m_scene; }
};

#endif