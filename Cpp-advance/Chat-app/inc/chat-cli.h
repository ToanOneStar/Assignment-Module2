#ifndef CHAT_CLI_H
#define CHAT_CLI_H

#include <string>

class ChatServer;

bool connectToPeer(const std::string& ip, int port);
void listPeers();
void sendMessage(int peerId, const std::string& message);
void terminatePeer(int peerId);

void runCli(ChatServer& server);

#endif // CHAT_CLI_H