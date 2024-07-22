#include "CommandInterpreter.h"

#include "PlayerType.h"

CommandInterpreter::CommandInterpreter(Manager& manager) : _manager(manager) {}

CommandInterpreter::GameCmds CommandInterpreter::hashGameCommand(const std::string& cmd) {
    if (cmd == "Game") {
        return GameCmds::CMD_GAME;
    } else if (cmd == "Resign") {
        return GameCmds::CMD_RESIGN;
    } else if (cmd == "Move") {
        return GameCmds::CMD_MOVE;
    } else if (cmd == "Setup") {
        return GameCmds::CMD_SETUP;
    } else {
        return GameCmds::CMD_UNKNOWN;
    }
}

void CommandInterpreter::processGameInput() {
    std::string cmd;
    _in >> cmd;

    switch (hashGameCommand(cmd)) {
        case GameCmds::CMD_GAME: {
            std::string white, black;
            _in >> white >> black;
            PlayerType::Type whiteType = PlayerType::HashPlayerType(white);
            PlayerType::Type blackType = PlayerType::HashPlayerType(black);
            _manager.startGame(whiteType, blackType);
            break;
        }
        case GameCmds::CMD_RESIGN:
            std::cout << "Player resigned" << std::endl;
            break;
        case GameCmds::CMD_MOVE:
            std::cout << "Player moved" << std::endl;
            break;
        case GameCmds::CMD_SETUP:
            std::cout << "Player set up" << std::endl;
            break;
        case GameCmds::CMD_UNKNOWN:  // equivalent to default
            throw std::invalid_argument("Invalid command");
            break;
    }
}

void CommandInterpreter::processSetupInput() {
}