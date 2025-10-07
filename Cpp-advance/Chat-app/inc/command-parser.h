#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>
#include <vector>

class CommandParser {
public:
    struct Command {
        std::string action;
        std::vector<std::string> args;
    };
    
    static Command parse(const std::string& input);
    static void printHelp();
};

#endif