#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include <iostream>
#include <string>

#include "Manager.h"

class CommandInterpreter {
    std::istream& _in = std::cin;  // default
    Manager& _manager;

    // enum class to ensure type safety
    enum class GameCmds {
        CMD_GAME,
        CMD_RESIGN,
        CMD_MOVE,
        CMD_SETUP,
        CMD_UNKNOWN
    };

    GameCmds hashGameCommand(const std::string& cmd);

   public:
    CommandInterpreter(Manager& manager);
    void processGameInput();
    void processSetupInput();
};
#endif