#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include <iostream>
#include <memory>
#include <string>

#include "../Game/Game.h"
#include "../Manager/Manager.h"
#include "../Player/Player.h"
#include "../SetupInstruction/SetupInstruction.h"
#include "PromotionCmds.h"

class CommandInterpreter {
    CommandInterpreter();
    static std::istream& _in;

    // enum class to ensure type safety
    enum class GameCmds {
        CMD_GAME,
        CMD_SCORE,
        CMD_RESIGN,
        CMD_MOVE,
        CMD_SETUP,
        CMD_UNKNOWN,
        CMD_END
    };

    static GameCmds hashGameCommand(const std::string& cmd);
    static GameCmds hashPlayerCommand(const std::string& cmd);
    static SetupCmds hashSetupCommand(const std::string& cmd);

   public:
    CommandInterpreter(CommandInterpreter const&) = delete;
    CommandInterpreter& operator=(CommandInterpreter const&) = delete;

    static std::shared_ptr<CommandInterpreter> instance() {
        static std::shared_ptr<CommandInterpreter> ci{new CommandInterpreter};
        return ci;
    }

    static bool processGameInput();
    static Move processPlayerInput(Player& player);
    static SetupInstruction processSetupInput();
    static PromotionType::Type processPromotionInput();
};
#endif