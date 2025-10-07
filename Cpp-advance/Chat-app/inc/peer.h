#ifndef PEER_H
#define PEER_H

#include <string>
#include <arpa/inet.h>

class Peer {
private:
    int id;
    std::string ipAddress;
    int port;
    int socketFd;

public:
    Peer(int id, const std::string& ip, int port, int sockFd);
    ~Peer();
    
    int getId() const { return id; }
    std::string getIpAddress() const { return ipAddress; }
    int getPort() const { return port; }
    int getSocketFd() const { return socketFd; }
    
    void setSocketFd(int sockFd) { socketFd = sockFd; }
};

#endif