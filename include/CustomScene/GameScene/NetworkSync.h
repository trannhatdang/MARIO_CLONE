#ifndef NETWORK_SYNC_H_
#define NETWORK_SYNC_H_

#include "engine/Components/Component.h"
#include "engine/Components/Transform.h"
#include "engine/Components/Rigidbody.h"
#include "Network.h"
#include "Player.h"

class NetworkSync : public Component
{
private:
    Network* m_network;
    GameObject* m_player;
    bool m_isLocal; // if true, send, else receive
    int m_lastShootCounter = 0;  // Track last received shoot counter
    int m_lastDestroyCounter = 0;  // Track last received block destroy counter
    bool m_hasSpawnedRemotePlayer = false;  // Track if this component has triggered remote player spawn

public:
    NetworkSync(GameObject* obj, Network* network, bool isLocal);
    ~NetworkSync();
    void OnIterate();
    std::unique_ptr<Component> copy();
};

#endif