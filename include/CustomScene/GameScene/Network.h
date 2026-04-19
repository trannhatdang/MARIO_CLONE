#ifndef NETWORK_H_
#define NETWORK_H_

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <vector>
#include "engine/main.h" // for Vector3

#pragma comment(lib, "ws2_32.lib")

#pragma pack(push, 1)
struct PlayerData {
    int posX, posY, posZ;           // Vector3 position
    float velX, velY, velZ;         // Vector3f velocity
    bool isFacingLeft;
    bool isRunning;
    bool isOnGround;
    bool isActing;
    int shootCounter;               // Incremented when player shoots
    int blockDestroyCounter;        // Incremented when block is destroyed
    int blockDestroyType;           // 1=star, 2=superpunch, 0=none
    int blockDestroyPosX, blockDestroyPosY, blockDestroyPosZ;  // Position of destroyed item
    bool sniper1Dead;               // Enemy death states (synced across clients)
    bool sniper2Dead;
    bool bossDead;
};
#pragma pack(pop)

class Network {
private:
    bool isServer;
    SOCKET sock;
    sockaddr_in serverAddr;
    sockaddr_in clientAddr;
    int clientAddrLen;

    std::string serverIP;
    int port;

public:
    Network(bool server, const std::string& ip = "127.0.0.1", int p = 12345);
    ~Network();

    bool Init();
    void SendPlayerData(const PlayerData& data);
    bool ReceivePlayerData(PlayerData& data);
    void Cleanup();
};

#endif