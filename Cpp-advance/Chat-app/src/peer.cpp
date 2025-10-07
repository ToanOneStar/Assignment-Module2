#include "peer.h"
#include <unistd.h>

Peer::Peer(int id, const std::string& ip, int port, int sockFd)
    : id(id), ipAddress(ip), port(port), socketFd(sockFd) {}

Peer::~Peer() {
    if (socketFd > 0) {
        close(socketFd);
    }
}