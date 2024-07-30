#include "Manager.h"

#include <iostream>

#include "../CommandInterpreter/CommandInterpreter.h"
#include "../Game/Game.h"
#include "../PlayerType/PlayerType.h"
#include "../enums.h"

std::shared_ptr<Game> Manager::_CurrGame = nullptr;
std::unique_ptr<LeaderBoard> Manager::_leaderBoard = nullptr;

Manager::Manager() {}

int Manager::_turn = 0;

void Manager::setupGame() {
    _CurrGame = std::make_shared<Game>();
    _CurrGame->setupBoard();
}

void Manager::startGame(PlayerType::Type white, PlayerType::Type black) {
    // if there's no custom setup game that already exists, create a new one with default settings
    if (_CurrGame == nullptr) {
        _CurrGame = std::make_shared<Game>();
        _CurrGame->initDefaultGame();
    }
    _CurrGame->setupPlayers(white, black);

    _CurrGame->renderBoard();

    // Game loop
    while (true) {

        // Check for checks
        bool is_white = _turn == 0;
        Color player_color = is_white ? Color::WHITE : Color::BLACK;
        Color opponent_color = is_white ? Color::BLACK : Color::WHITE;
        bool in_check = is_white ? _CurrGame->getWhite().inCheck() : _CurrGame->getBlack().inCheck();

        // Check if player has any valid moves in this position
        bool any_valid_moves = _CurrGame->anyValidMoves(player_color);
        if (!any_valid_moves && in_check) {
            std::cout << player_color << " is checkmated! " << opponent_color << " wins!" << std::endl;
            break;
        } else if (!any_valid_moves && !in_check) {
            std::cout << "Stalemate! It's a draw!" << std::endl;
            break;
        }

        std::cout << player_color << "'s turn." << std::endl;

        if (in_check) {
            std::cout << player_color << " is in check." << std::endl;
        }

        Move next_move = _turn == 0 ? _CurrGame->getWhite().getMove() : _CurrGame->getBlack().getMove();
        if (!_CurrGame) break;  // if player resigns

        // invalid move flag is {(-1, -1), (-1, -1)}
        if (next_move.type == MoveType::INVALID) {
            std::cout << "Enter a valid command" << std::endl;
            continue;
        }

        // invalid move, no warning flag is {(-2 -2), (-2, -2)}
        if (next_move.type == MoveType::INVALID_NO_FLAG) {
            continue;
        }

        // Player has valid moves: allow them to play their turn
        if (!_CurrGame->makeTurn(next_move, static_cast<Color>(_turn), in_check)) {
            std::cout << "Invalid move." << std::endl
                      << std::endl;
            continue;
        }

        // // for debugging
        // for (auto i : _CurrGame->getBlack()._alive_pieces) {
        //     std::cout << i->getPieceChar() << " ";
        // }

        // std::cout << std::endl;

        // for (auto i : _CurrGame->getWhite()._alive_pieces) {
        //     std::cout << i->getPieceChar() << " ";
        // }

        // std::cout << std::endl;

        _turn = (_turn + 1) % 2;
    }
}

void Manager::closeGame() {
    std::cout << "Game over" << std::endl;
    _CurrGame = nullptr;
}

void Manager::setTurn(Color color) {
    _turn = static_cast<int>(color);
}

LeaderBoard& Manager::getLeaderBoard() {
    if (_leaderBoard == nullptr) {
        _leaderBoard = std::make_unique<LeaderBoard>();
    }

    return *_leaderBoard;
}