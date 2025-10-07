#include "chat-server.h"
#include "command-parser.h"
#include "connection-manager.h"
#include "chat-cli.h"
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

bool connectToPeer(const std::string& ip, int port) {
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0) {
        std::cerr << "Error creating socket for connection" << std::endl;
        return false;
    }
    
    sockaddr_in peerAddr;

    std::memset(&peerAddr, 0, sizeof(peerAddr));
    peerAddr.sin_family = AF_INET;
    peerAddr.sin_port = htons(port);
    
    if (inet_pton(AF_INET, ip.c_str(), &peerAddr.sin_addr) <= 0) {
        std::cerr << "Invalid IP address" << std::endl;
        close(sockFd);
        return false;
    }
    
    if (connect(sockFd, reinterpret_cast<sockaddr*>(&peerAddr), sizeof(peerAddr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        close(sockFd);
        return false;
    }
    
    ConnectionManager* connManager = ConnectionManager::getInstance();
    int peerId = connManager->addPeer(ip, port, sockFd);
    
    std::cout << "Connected to peer " << ip << ":" << port << " (ID: " << peerId << ")" << std::endl;
    return true;
}

void listPeers() {
    ConnectionManager* connManager = ConnectionManager::getInstance();
    auto peers = connManager->getAllPeers();
    
    if (peers.empty()) {
        std::cout << "No connected peers" << std::endl;
        return;
    }
    
    std::cout << "\n=== Connected Peers ===" << std::endl;
    std::cout << "ID | IP Address | Port" << std::endl;
    std::cout << "------------------------" << std::endl;
    
    for (const auto& peer : peers) {
        std::cout << peer->getId() << " | " << peer->getIpAddress() 
                  << " | " << peer->getPort() << std::endl;
    }
    std::cout << std::endl;
}

void sendMessage(int peerId, const std::string& message) {
    ConnectionManager* connManager = ConnectionManager::getInstance();
    auto peer = connManager->findPeer(peerId);
    
    if (peer == nullptr) {
        std::cerr << "Peer ID not found" << std::endl;
        return;
    }
    
    ssize_t bytesSent = send(peer->getSocketFd(), message.c_str(), message.length(), 0);
    
    if (bytesSent < 0) {
        std::cerr << "Error sending message" << std::endl;
    } else {
        std::cout << "Message sent to peer " << peerId << std::endl;
    }
}

void terminatePeer(int peerId) {
    ConnectionManager* connManager = ConnectionManager::getInstance();
    auto peer = connManager->findPeer(peerId);
    
    if (peer == nullptr) {
        std::cerr << "Peer ID not found" << std::endl;
        return;
    }
    
    close(peer->getSocketFd());
    connManager->removePeer(peerId);
    std::cout << "Connection to peer " << peerId << " terminated" << std::endl;
}

void runCli(ChatServer& server) {
    std::string input;
    bool running = true;

    std::cout << "\n=== P2P Chat Application ===" << std::endl;
    std::cout << "Type 'help' for available commands\n" << std::endl;

    while (running) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input.empty()) continue;

        auto cmd = CommandParser::parse(input);

        if (cmd.action == "connect") {
            if (cmd.args.size() < 2) {
                std::cerr << "Usage: connect <IP> <PORT>" << std::endl;
                continue;
            }
            connectToPeer(cmd.args[0], std::atoi(cmd.args[1].c_str()));

        } else if (cmd.action == "list") {
            listPeers();

        } else if (cmd.action == "send") {
            if (cmd.args.size() < 2) {
                std::cerr << "Usage: send <ID> <MESSAGE>" << std::endl;
                continue;
            }
            int peerId = std::atoi(cmd.args[0].c_str());
            std::string message = input.substr(input.find(cmd.args[1]));
            sendMessage(peerId, message);

        } else if (cmd.action == "terminate") {
            if (cmd.args.empty()) {
                std::cerr << "Usage: terminate <ID>" << std::endl;
                continue;
            }
            terminatePeer(std::atoi(cmd.args[0].c_str()));

        } else if (cmd.action == "myip") {
            std::cout << "Your IP: " << server.getIpAddress() << std::endl;

        } else if (cmd.action == "myport") {
            std::cout << "Your Port: " << server.getPort() << std::endl;

        } else if (cmd.action == "help") {
            CommandParser::printHelp();

        } else if (cmd.action == "exit") {
            std::cout << "Shutting down gracefully..." << std::endl;
            running = false;

        } else {
            std::cerr << "Unknown command. Type 'help' for available commands." << std::endl;
        }
    }

    server.stop();
    std::cout << "Application terminated." << std::endl;
}