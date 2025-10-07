#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

#include "peer.h"
#include <vector>
#include <memory>
#include <mutex>

class ConnectionManager {
private:
    static ConnectionManager* instance;
    static std::mutex instanceMutex;
    
    std::vector<std::shared_ptr<Peer>> peers;
    std::mutex peersMutex;
    int nextId;
    
    ConnectionManager();
    
public:
    static ConnectionManager* getInstance();
    ~ConnectionManager();
    
    ConnectionManager(const ConnectionManager&) = delete;
    ConnectionManager& operator=(const ConnectionManager&) = delete;
    
    int addPeer(const std::string& ip, int port, int sockFd);
    bool removePeer(int id);
    std::shared_ptr<Peer> findPeer(int id);
    std::vector<std::shared_ptr<Peer>> getAllPeers();
    void clearAllPeers();
};

#endif