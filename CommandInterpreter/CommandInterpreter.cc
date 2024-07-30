#include "CommandInterpreter.h"

#include <limits>
#include <memory>
#include <string>

#include "../Game/Game.h"
#include "../Move/Move.h"
#include "../Player/Player.h"
#include "../PlayerType/PlayerType.h"
#include "../SetupInstruction/SetupInstruction.h"

std::istream& CommandInterpreter::_in = std::cin;

CommandInterpreter::GameCmds CommandInterpreter::hashGameCommand(
    const std::string& cmd) {
    if (cmd == "game") {
        return GameCmds::CMD_GAME;
    } else if (cmd == "setup") {
        return GameCmds::CMD_SETUP;
    } else if (cmd == "end") {
        return GameCmds::CMD_END;
    } else {
        return GameCmds::CMD_UNKNOWN;
    }
}

CommandInterpreter::GameCmds CommandInterpreter::hashPlayerCommand(
    const std::string& cmd) {
    if (cmd == "resign") {
        return GameCmds::CMD_RESIGN;
    } else if (cmd == "move") {
        return GameCmds::CMD_MOVE;
    } else if (cmd == "peek") {
        return GameCmds::CMD_PEEK;
    } else {
        return GameCmds::CMD_UNKNOWN;
    }
}

SetupCmds CommandInterpreter::hashSetupCommand(
    const std::string& cmd) {
    if (cmd == "+") {
        return SetupCmds::CMD_ADD_PIECE;
    } else if (cmd == "-") {
        return SetupCmds::CMD_REMOVE_PIECE;
    } else if (cmd == "=") {
        return SetupCmds::CMD_SET_TURN;
    } else if (cmd == "done") {
        return SetupCmds::CMD_SETUP_DONE;
    } else {
        return SetupCmds::CMD_UNKNOWN;
    }
}

bool CommandInterpreter::processGameInput() {
    std::string cmd;
    _in >> cmd;

    switch (hashGameCommand(cmd)) {
        case GameCmds::CMD_SETUP:
            Manager::setupGame();
            return true;
            break;
        case GameCmds::CMD_GAME: {
            std::string white, black;
            _in >> white >> black;
            PlayerType::Type whiteType = PlayerType::HashPlayerType(white);
            PlayerType::Type blackType = PlayerType::HashPlayerType(black);
            Manager::startGame(whiteType, blackType);
            return true;
            break;
        }
        case GameCmds::CMD_END:
            return false;
            break;
        case GameCmds::CMD_UNKNOWN:  // equivalent to default
            throw std::invalid_argument("Invalid command");
            break;
    }

    return false;
}

// Passing in a Game reference so Manager can run multiple games at once
Move CommandInterpreter::processPlayerInput(Player& player) {
    std::string cmd;
    _in >> cmd;

    switch (hashPlayerCommand(cmd)) {
        case GameCmds::CMD_RESIGN:
            player.resign();
            break;
        case GameCmds::CMD_MOVE: {
            char og_col, new_col;
            int og_row, new_row;
            _in >> og_col >> og_row >> new_col >> new_row;
            if (_in.fail()) {
                _in.clear();
                _in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return Move(Position{-1, -1}, Position{-1, -1}, MoveType::INVALID);
            }
            if (8 - og_row < 0 || 8 - og_row > 7 || (int)og_col - 97 < 0 || (int)og_col - 97 > 7 ||
                8 - new_row < 0 || 8 - new_row > 7 || (int)new_col - 97 < 0 || (int)new_col - 97 > 7) {
                return Move(Position{-1, -1}, Position{-1, -1}, MoveType::INVALID);
            }

            Move move(Position{8 - og_row, (int)og_col - 97},
                      Position{8 - new_row, (int)new_col - 97});
            return move;
            break;
        }
        case GameCmds::CMD_PEEK: {
            char col;
            int row;
            _in >> col >> row;
            if (_in.fail()) {
                _in.clear();
                _in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return Move(Position{-1, -1}, Position{-1, -1}, MoveType::INVALID);
            }
            if (8 - row < 0 || 8 - row > 7 || (int)col - 97 < 0 || (int)col - 97 > 7) {
                return Move(Position{-1, -1}, Position{-1, -1}, MoveType::INVALID);
            }
            Manager::getCurrGame()->peek(Position{8 - row, (int)col - 97}, player.getColor());
            return Move(Position{-1, -1}, Position{-1, -1}, MoveType::INVALID_NO_FLAG);
            break;
        }
        case GameCmds::CMD_UNKNOWN:  // equivalent to default
            return Move(Position{-1, -1}, Position{-1, -1}, MoveType::INVALID);
            break;
    }
}

SetupInstruction CommandInterpreter::processSetupInput() {
    std::string cmd;
    _in >> cmd;
    SetupCmds setupCmd = hashSetupCommand(cmd);

    switch (setupCmd) {
        case SetupCmds::CMD_ADD_PIECE: {
            char piece;
            Position pos;
            _in >> piece >> pos;
            return SetupInstruction{setupCmd, piece, pos};
            break;
        }
        case SetupCmds::CMD_REMOVE_PIECE: {
            Position pos;
            _in >> pos;
            return SetupInstruction{setupCmd, pos};
            break;
        }
        case SetupCmds::CMD_SET_TURN:
            Color color;
            _in >> color;
            return SetupInstruction{setupCmd, color};
            break;
        case SetupCmds::CMD_SETUP_DONE:
            return SetupInstruction{setupCmd};
            break;
        case SetupCmds::CMD_UNKNOWN:  // equivalent to default
            throw std::invalid_argument("Invalid command");
            break;
    }
}

PromotionType::Type CommandInterpreter::processPromotionInput() {
    std::cout << "Choose a piece to promote to (q, r, b, n): ";

    char cmd;
    _in >> cmd;

    PromotionType::Type promotionType = PromotionType::HashPromotionType(cmd);
    return promotionType;
}
