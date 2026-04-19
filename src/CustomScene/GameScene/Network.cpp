#include "CustomScene/GameScene/Network.h"
#include <iostream>

Network::Network(bool server, const std::string& ip, int p) : isServer(server), serverIP(ip), port(p), clientAddrLen(0) {
    sock = INVALID_SOCKET;
}

Network::~Network() {
    Cleanup();
}

bool Network::Init() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return false;
    }

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr);

    if (isServer) {
        if (bind(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Bind failed" << std::endl;
            return false;
        }
    }

    // Set non-blocking
    u_long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode);

    return true;
}

void Network::SendPlayerData(const PlayerData& data) {
    if (isServer) {
        // Server only sends after it has received at least once from client
        if (clientAddrLen == 0) {
            // Haven't received from client yet, don't try to send
            return;
        }
        // Server sends to client
        int sentLen = sendto(sock, (char*)&data, sizeof(data), 0, (sockaddr*)&clientAddr, clientAddrLen);
        if (sentLen > 0) {
            std::cout << "[Server] Sent " << sentLen << " bytes to client" << std::endl;
        } else if (sentLen == SOCKET_ERROR) {
            std::cerr << "[Server] SendPlayerData error: " << WSAGetLastError() << std::endl;
        }
    } else {
        // Client sends to server
        int sentLen = sendto(sock, (char*)&data, sizeof(data), 0, (sockaddr*)&serverAddr, sizeof(serverAddr));
        if (sentLen > 0) {
            std::cout << "[Client] Sent " << sentLen << " bytes to server" << std::endl;
        } else if (sentLen == SOCKET_ERROR) {
            std::cerr << "[Client] SendPlayerData error: " << WSAGetLastError() << std::endl;
        }
    }
}

bool Network::ReceivePlayerData(PlayerData& data) {
    int recvLen;
    int addrLen = sizeof(serverAddr);
    if (isServer) {
        int clientAddrLen_temp = sizeof(clientAddr);  // Must be set before recvfrom
        recvLen = recvfrom(sock, (char*)&data, sizeof(data), 0, (sockaddr*)&clientAddr, &clientAddrLen_temp);
        if (recvLen == sizeof(data)) {
            clientAddrLen = clientAddrLen_temp;  // Save address for sending back
            std::cout << "[Server] Received " << recvLen << " bytes from client" << std::endl;
            return true;
        } else if (recvLen == SOCKET_ERROR) {
            int err = WSAGetLastError();
            if (err != WSAEWOULDBLOCK) {
                std::cerr << "[Server] ReceivePlayerData error: " << err << std::endl;
            }
        }
    } else {
        recvLen = recvfrom(sock, (char*)&data, sizeof(data), 0, (sockaddr*)&serverAddr, &addrLen);
        if (recvLen == sizeof(data)) {
            std::cout << "[Client] Received " << recvLen << " bytes from server" << std::endl;
            return true;
        } else if (recvLen == SOCKET_ERROR) {
            int err = WSAGetLastError();
            if (err != WSAEWOULDBLOCK) {
                std::cerr << "[Client] ReceivePlayerData error: " << err << std::endl;
            }
        }
    }
    return false;
}

void Network::Cleanup() {
    if (sock != INVALID_SOCKET) {
        closesocket(sock);
    }
    WSACleanup();
}