#include "CommandInterpreter.h"

#include "Game.h"
#include "Move.h"
#include "Player.h"
#include "PlayerType.h"

std::istream& CommandInterpreter::_in = std::cin;

CommandInterpreter::GameCmds CommandInterpreter::hashGameCommand(const std::string& cmd) {
    if (cmd == "Game") {
        return GameCmds::CMD_GAME;
    } else if (cmd == "Setup") {
        return GameCmds::CMD_SETUP;
    } else {
        return GameCmds::CMD_UNKNOWN;
    }
}

CommandInterpreter::GameCmds CommandInterpreter::hashPlayerCommand(const std::string& cmd) {
    if (cmd == "Resign") {
        return GameCmds::CMD_RESIGN;
    } else if (cmd == "Move") {
        return GameCmds::CMD_MOVE;
    } else {
        return GameCmds::CMD_UNKNOWN;
    }
}

void CommandInterpreter::processGameInput() {
    std::string cmd;
    _in >> cmd;

    switch (hashGameCommand(cmd)) {
        case GameCmds::CMD_RESIGN:
            Manager::closeGame();
            break;
        case GameCmds::CMD_MOVE:
            std::cout << "Player moved" << std::endl;
            break;

        case GameCmds::CMD_UNKNOWN:  // equivalent to defaults
            throw std::invalid_argument("Invalid command");
            break;
    }
}

// Passing in a Game reference so Manager can run multiple games at once
void CommandInterpreter::processPlayerInput(Game& Game, Player& player) {
    std::string cmd;
    _in >> cmd;

    switch (hashPlayerCommand(cmd)) {
        case GameCmds::CMD_RESIGN:
            player.resign();
            break;
        case GameCmds::CMD_MOVE: {
            char og_col, og_row, new_col, new_row;
            _in >> og_col >> og_row >> new_col >> new_row;
            Move move(Position{og_col, og_row}, Position{new_col, new_row});
            Game.makeTurn(move);
            break;
        }
        case GameCmds::CMD_UNKNOWN:  // equivalent to default
            throw std::invalid_argument("Invalid command");
            break;
    }
}

void CommandInterpreter::processSetupInput() {
}