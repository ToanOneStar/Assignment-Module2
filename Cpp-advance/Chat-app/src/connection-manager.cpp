#include "connection-manager.h"
#include <algorithm>

ConnectionManager* ConnectionManager::instance = nullptr;
std::mutex ConnectionManager::instanceMutex;

ConnectionManager::ConnectionManager() : nextId(1) {}

ConnectionManager* ConnectionManager::getInstance() {
    if (instance == nullptr) {
        std::lock_guard<std::mutex> lock(instanceMutex);
        if (instance == nullptr) {
            instance = new ConnectionManager();
        }
    }
    return instance;
}

ConnectionManager::~ConnectionManager() {
    clearAllPeers();
}

int ConnectionManager::addPeer(const std::string& ip, int port, int sockFd) {
    std::lock_guard<std::mutex> lock(peersMutex);
    int id = nextId++;
    auto peer = std::make_shared<Peer>(id, ip, port, sockFd);
    peers.push_back(peer);
    return id;
}

bool ConnectionManager::removePeer(int id) {
    std::lock_guard<std::mutex> lock(peersMutex);
    auto it = std::remove_if(peers.begin(), peers.end(),
        [id](const std::shared_ptr<Peer>& p) { return p->getId() == id; });
    
    if (it != peers.end()) {
        peers.erase(it, peers.end());
        return true;
    }
    return false;
}

std::shared_ptr<Peer> ConnectionManager::findPeer(int id) {
    std::lock_guard<std::mutex> lock(peersMutex);
    for (auto& peer : peers) {
        if (peer->getId() == id) {
            return peer;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Peer>> ConnectionManager::getAllPeers() {
    std::lock_guard<std::mutex> lock(peersMutex);
    return peers;
}

void ConnectionManager::clearAllPeers() {
    std::lock_guard<std::mutex> lock(peersMutex);
    peers.clear();
}