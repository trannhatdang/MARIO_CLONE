#include "CustomScene/GameScene/NetworkSync.h"
#include "CustomScene/GameScene/Star.h"
#include "CustomScene/GameScene/SuperPunch.h"
#include "CustomScene/GameScene/Sniper.h"
#include "CustomScene/GameScene/Boss.h"

// Forward declaration
void SpawnRemotePlayer(Scene* gameScene);

// External declaration  
extern Scene* g_currentGameScene;
extern GameObject* g_sniper1;
extern GameObject* g_sniper2;
extern GameObject* g_boss;

NetworkSync::NetworkSync(GameObject* obj, Network* network, bool isLocal) : Component("NetworkSync", obj), m_network(network), m_isLocal(isLocal)
{
    m_player = obj;
}

NetworkSync::~NetworkSync()
{

}

void NetworkSync::OnIterate()
{
    if (!m_network) return;

    if (m_isLocal) {
        // Send own data
        PlayerData data = {};  // Zero-initialize all fields
        Vector3 pos = m_player->GetTransform()->GetPosition();
        data.posX = pos.x;
        data.posY = pos.y;
        data.posZ = pos.z;
        
        Rigidbody* rb = static_cast<Rigidbody*>(m_player->GetComponent("Rigidbody"));
        if (rb) {
            Vector3f vel = rb->GetVelocity();
            data.velX = vel.x;
            data.velY = vel.y;
            data.velZ = vel.z;
        } else {
            data.velX = data.velY = data.velZ = 0.f;
        }
        
        Player* p = static_cast<Player*>(m_player->GetComponent("Player"));
        if (p) {
            data.isFacingLeft = p->IsFacingLeft();
            data.isRunning = p->IsRunning();
            data.isOnGround = p->IsOnGround();
            data.isActing = p->IsActing();
            data.shootCounter = p->GetShootCounter();
            data.blockDestroyCounter = p->GetBlockDestroyCounter();
            data.blockDestroyType = p->GetBlockDestroyType();
            Vector3 destroyPos = p->GetBlockDestroyPos();
            data.blockDestroyPosX = destroyPos.x;
            data.blockDestroyPosY = destroyPos.y;
            data.blockDestroyPosZ = destroyPos.z;
        } else {
            data.isFacingLeft = data.isRunning = data.isOnGround = data.isActing = false;
            data.shootCounter = 0;
            data.blockDestroyCounter = 0;
            data.blockDestroyType = 0;
            data.blockDestroyPosX = data.blockDestroyPosY = data.blockDestroyPosZ = 0;
        }

        // Collect enemy death states
        if (g_sniper1) {
            Sniper* s1 = static_cast<Sniper*>(g_sniper1->GetComponent("Sniper"));
            data.sniper1Dead = s1 && s1->IsDead();
        }
        if (g_sniper2) {
            Sniper* s2 = static_cast<Sniper*>(g_sniper2->GetComponent("Sniper"));
            data.sniper2Dead = s2 && s2->IsDead();
        }
        if (g_boss) {
            Boss* b = static_cast<Boss*>(g_boss->GetComponent("Boss"));
            data.bossDead = b && b->IsDead();
        }

        m_network->SendPlayerData(data);

        // Also receive remote player data (so we can spawn and update remote player)
        PlayerData remoteData = {};
        if (m_network->ReceivePlayerData(remoteData)) {
            std::cout << "[NetworkSync] Local player received remote data" << std::endl;
            
            // Spawn remote player on first successful data reception
            if (!m_hasSpawnedRemotePlayer && g_currentGameScene) {
                m_hasSpawnedRemotePlayer = true;
                std::cout << "\n===== REMOTE PLAYER CONNECTION DETECTED =====" << std::endl;
                std::cout << "Remote player data received! Spawning remote player..." << std::endl;
                SpawnRemotePlayer(g_currentGameScene);
                std::cout << "Remote player spawned and ready to sync!" << std::endl;
                std::cout << "====== CONNECTION ESTABLISHED ======\n" << std::endl;
            }

            // Apply enemy death states from remote player
            if (remoteData.sniper1Dead && g_sniper1 && g_sniper1->GetEnabled()) {
                g_sniper1->SetActive(false);
                std::cout << "[NetworkSync] Sniper 1 deactivated (remote death synced)" << std::endl;
            }
            if (remoteData.sniper2Dead && g_sniper2 && g_sniper2->GetEnabled()) {
                g_sniper2->SetActive(false);
                std::cout << "[NetworkSync] Sniper 2 deactivated (remote death synced)" << std::endl;
            }
            if (remoteData.bossDead && g_boss && g_boss->GetEnabled()) {
                g_boss->SetActive(false);
                std::cout << "[NetworkSync] Boss deactivated (remote death synced)" << std::endl;
            }
        }
    } else {
        // Receive data (for remote player entity)
        PlayerData data = {};  // Zero-initialize all fields
        if (m_network->ReceivePlayerData(data)) {
            std::cout << "[NetworkSync] Remote player entity received data" << std::endl;
            
            // Spawn remote player on first successful data reception (backup spawn if local didn't do it)
            if (!m_hasSpawnedRemotePlayer && g_currentGameScene) {
                m_hasSpawnedRemotePlayer = true;
                std::cout << "\n===== REMOTE PLAYER CONNECTION DETECTED =====" << std::endl;
                std::cout << "Remote player data received! Spawning remote player..." << std::endl;
                SpawnRemotePlayer(g_currentGameScene);
                std::cout << "Remote player spawned and ready to sync!" << std::endl;
                std::cout << "====== CONNECTION ESTABLISHED ======\n" << std::endl;
            }
            m_player->GetTransform()->SetPosition(Vector3(data.posX, data.posY, data.posZ));
            
            Rigidbody* rb = static_cast<Rigidbody*>(m_player->GetComponent("Rigidbody"));
            if (rb) rb->SetVelocity(Vector3f(data.velX, data.velY, data.velZ));
            
            Player* p = static_cast<Player*>(m_player->GetComponent("Player"));
            if (p) {
                p->SetFacingLeft(data.isFacingLeft);
                p->SetRunning(data.isRunning);
                p->SetOnGround(data.isOnGround);
                p->SetActing(data.isActing);
                
                // Check if player shot (shootCounter changed)
                if (data.shootCounter != m_lastShootCounter) {
                    m_lastShootCounter = data.shootCounter;
                    p->CreateBulletFromNetwork();
                }
                
                // Check if block destroyed (destroyCounter changed)
                if (data.blockDestroyCounter != m_lastDestroyCounter && data.blockDestroyType != 0) {
                    m_lastDestroyCounter = data.blockDestroyCounter;
                    
                    // Spawn item at destroyed position
                    Scene* scene = p->GetScene();
                    if (scene) {
                        GameObject* newItem = nullptr;
                        Vector3 itemPos(data.blockDestroyPosX, data.blockDestroyPosY, data.blockDestroyPosZ);
                        
                        if (data.blockDestroyType == 1) {
                            // Star item
                            newItem = scene->AddGameObject("Star", "Star");
                            newItem->AddComponent(new Star(newItem));
                            newItem->AddComponent(new SpriteRenderer(newItem, scene->GetRenderer(), GetStarSprite(), { 0, 0, 0 }, { 0, 0, 100, 100 }, { 0, 0, 25, 25 }));
                        } else if (data.blockDestroyType == 2) {
                            // SuperPunch item
                            newItem = scene->AddGameObject("SuperPunch", "SuperPunch");
                            newItem->AddComponent(new SuperPunch(newItem));
                            newItem->AddComponent(new SpriteRenderer(newItem, scene->GetRenderer(), GetSuperPunchSprite(), { 0, 0, 0 }, { 0, 0, 100, 100 }, { 0, 0, 25, 25 }));
                        }
                        
                        if (newItem) {
                            newItem->AddComponent(new BoxCollider(newItem, { 25, 25 }, true, true));
                            newItem->GetTransform()->SetPosition(itemPos);
                        }
                    }
                }

                // Apply enemy death states from local player
                if (data.sniper1Dead && g_sniper1 && g_sniper1->GetEnabled()) {
                    g_sniper1->SetActive(false);
                    std::cout << "[NetworkSync] Sniper 1 deactivated (local death synced)" << std::endl;
                }
                if (data.sniper2Dead && g_sniper2 && g_sniper2->GetEnabled()) {
                    g_sniper2->SetActive(false);
                    std::cout << "[NetworkSync] Sniper 2 deactivated (local death synced)" << std::endl;
                }
                if (data.bossDead && g_boss && g_boss->GetEnabled()) {
                    g_boss->SetActive(false);
                    std::cout << "[NetworkSync] Boss deactivated (local death synced)" << std::endl;
                }
            }
        }
    }
}

std::unique_ptr<Component> NetworkSync::copy()
{
    return std::make_unique<NetworkSync>(gameObject, m_network, m_isLocal);
}