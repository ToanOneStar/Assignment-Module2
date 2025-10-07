#include "chat-server.h"
#include "command-parser.h"
#include "connection-manager.h"
#include "chat-cli.h"
#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: ./chat_app <IP_ADDRESS> <PORT>" << std::endl;
        std::cout << "Example: ./chat_app 127.0.0.1 8080" << std::endl;
        return 1;
    }
    
    std::string ipAddress = argv[1];
    int port = std::atoi(argv[2]);
    
    if (port <= 0 || port > 65535) {
        std::cerr << "Invalid port number" << std::endl;
        return 1;
    }
    
    ChatServer server(ipAddress, port);
    if (!server.start()) {
        std::cerr << "Failed to start server" << std::endl;
        return 1;
    }
    
    runCli(server);
    return 0;
}