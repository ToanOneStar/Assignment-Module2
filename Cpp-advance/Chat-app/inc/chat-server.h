#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include "connection-manager.h"
#include <string>
#include <thread>
#include <atomic>

class ChatServer {
private:
    int serverSocket;
    int port;
    std::string ipAddress;
    std::atomic<bool> running;
    std::thread acceptThread;
    ConnectionManager* connManager;
    
    void acceptConnections();
    void handleClient(int clientSocket, const std::string& clientIp, int clientPort);
    
public:
    ChatServer(const std::string& ip, int port);
    ~ChatServer();
    
    bool start();
    void stop();
    std::string getIpAddress() const { return ipAddress; }
    int getPort() const { return port; }
};

#endif