#include "command-parser.h"
#include <sstream>
#include <iostream>

CommandParser::Command CommandParser::parse(const std::string& input) {
    Command cmd;
    std::istringstream iss(input);
    iss >> cmd.action;
    
    std::string arg;
    while (iss >> arg) {
        cmd.args.push_back(arg);
    }
    
    return cmd;
}

void CommandParser::printHelp() {
    std::cout << "\n=== Available Commands ===" << std::endl;
    std::cout << "connect <IP> <PORT>  - Connect to a peer" << std::endl;
    std::cout << "list                 - List all connected peers" << std::endl;
    std::cout << "send <ID> <MESSAGE>  - Send message to peer" << std::endl;
    std::cout << "terminate <ID>       - Disconnect from peer" << std::endl;
    std::cout << "myip                 - Show your IP address" << std::endl;
    std::cout << "myport               - Show your listening port" << std::endl;
    std::cout << "help                 - Show this help message" << std::endl;
    std::cout << "exit                 - Exit the application" << std::endl;
    std::cout << "========================\n" << std::endl;
}