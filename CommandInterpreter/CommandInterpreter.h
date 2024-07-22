#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include <iostream>
#include <memory>
#include <string>

#include "Manager.h"

class Player;
class Game;

class CommandInterpreter {
    CommandInterpreter();
    static std::istream& _in;  // default

    // enum class to ensure type safety
    enum class GameCmds {
        CMD_GAME,
        CMD_RESIGN,
        CMD_MOVE,
        CMD_SETUP,
        CMD_UNKNOWN
    };

    static GameCmds hashGameCommand(const std::string& cmd);
    static GameCmds hashPlayerCommand(const std::string& cmd);

   public:
    CommandInterpreter(CommandInterpreter const&) = delete;
    CommandInterpreter& operator=(CommandInterpreter const&) = delete;

    static std::shared_ptr<CommandInterpreter> instance() {
        static std::shared_ptr<CommandInterpreter> ci{new CommandInterpreter};
        return ci;
    }

    static void processGameInput();
    static void processPlayerInput(const Game& Game, const Player& player);
    static void processSetupInput();
};
#endif