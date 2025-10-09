#include "chat-server.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <algorithm>
#include <cctype>

ChatServer::ChatServer(const std::string& ip, int port)
    : serverSocket(-1), port(port), ipAddress(ip), running(false) {
    connManager = ConnectionManager::getInstance();
}

ChatServer::~ChatServer() {
    stop();
}

bool ChatServer::start() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return false;
    }
    
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Error setting socket options" << std::endl;
        close(serverSocket);
        return false;
    }
    
    sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    
    // Trim whitespace from provided IP (helps catch accidental spaces in argv)
    std::string ipTrimmed = ipAddress;
    ipTrimmed.erase(ipTrimmed.begin(), std::find_if(ipTrimmed.begin(), ipTrimmed.end(), [](unsigned char ch){ return !std::isspace(ch); }));
    ipTrimmed.erase(std::find_if(ipTrimmed.rbegin(), ipTrimmed.rend(), [](unsigned char ch){ return !std::isspace(ch); }).base(), ipTrimmed.end());

    if (ipTrimmed.empty() || ipTrimmed == "0.0.0.0") {
        serverAddr.sin_addr.s_addr = INADDR_ANY;
    } else {
        if (inet_pton(AF_INET, ipTrimmed.c_str(), &serverAddr.sin_addr) <= 0) {
            std::cerr << "Invalid IP address: '" << ipTrimmed << "'" << std::endl;
            close(serverSocket);
            return false;
        }
    }
    
    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        close(serverSocket);
        return false;
    }
    
    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Error listening on socket" << std::endl;
        close(serverSocket);
        return false;
    }
    
    running = true;
    acceptThread = std::thread(&ChatServer::acceptConnections, this);
    
    std::cout << "Server started on " << ipTrimmed << ":" << port << std::endl;
    return true;
}

void ChatServer::acceptConnections() {
    while (running) {
        sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        
        int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddr), &clientLen);
        
        if (clientSocket < 0) {
            if (running) {
                std::cerr << "Error accepting connection" << std::endl;
            }
            continue;
        }
        
        char clientIp[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddr.sin_addr, clientIp, INET_ADDRSTRLEN);
        int clientPort = ntohs(clientAddr.sin_port);
        
        std::thread clientThread(&ChatServer::handleClient, this, clientSocket, std::string(clientIp), clientPort);
        clientThread.detach();
    }
}

void ChatServer::handleClient(int clientSocket, const std::string& clientIp, int clientPort) {
    int peerId = connManager->addPeer(clientIp, clientPort, clientSocket);
    std::cout << "\nNew connection from " << clientIp << ":" << clientPort << " (ID: " << peerId << ")" << std::endl;
    
    char buffer[4096];
    while (running) {
        std::memset(buffer, 0, sizeof(buffer));
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        
        if (bytesRead <= 0) {
            std::cout << "\nPeer " << peerId << " disconnected" << std::endl;
            break;
        }
        
        std::cout << "\nMessage from peer " << peerId << ": " << buffer << std::endl;
    }
    
    connManager->removePeer(peerId);
    close(clientSocket);
}

void ChatServer::stop() {
    if (running) {
        running = false;
        
        if (serverSocket >= 0) {
            shutdown(serverSocket, SHUT_RDWR);
            close(serverSocket);
            serverSocket = -1;
        }
        
        if (acceptThread.joinable()) {
            acceptThread.join();
        }
    }
}