#include "Manager.h"

#include <iostream>

#include "../CommandInterpreter/CommandInterpreter.h"
#include "../Game/Game.h"
#include "../PlayerType/PlayerType.h"
#include "../enums.h"

std::shared_ptr<Game> Manager::_CurrGame = nullptr;
std::unique_ptr<LeaderBoard> Manager::_leaderBoard = nullptr;

Manager::Manager() {}

void Manager::setupGame() {}

void Manager::startGame(PlayerType::Type white, PlayerType::Type black) {
    _CurrGame = std::make_shared<Game>(white, black);
    _CurrGame->initDefaultGame();

    _CurrGame->renderBoard();

    int turn_count = 0;

    // Game loop
    while (true) {
        // Check for checks
        bool is_white = turn_count % 2 == 0;
        Color player_color = is_white ? Color::WHITE : Color::BLACK;
        bool in_check = is_white ? _CurrGame->getWhite().inCheck() : _CurrGame->getBlack().inCheck();
        std::string player_color_string = is_white ? "White" : "Black";
        std::string opponent_color_string = is_white ? "Black" : "White";

        std::cout << player_color_string << "'s turn." << std::endl;

        // Check if player has any valid moves in this position
        bool any_valid_moves = _CurrGame->anyValidMoves(player_color);
        if (!any_valid_moves && in_check) {
            std::cout << player_color << " is checkmated! " << opponent_color_string << " wins!" << std::endl;
            break;
        } else if (!any_valid_moves && !in_check) {
            std::cout << "Stalemate! It's a draw!" << std::endl;
            break;
        }

        if (in_check) {
            std::cout << player_color_string << " is in check." << std::endl;
        }

        Move next_move = turn_count % 2 == 0 ? _CurrGame->getWhite().getMove() : _CurrGame->getBlack().getMove();

        if (!_CurrGame) break;  // if player resigns

        // Player has valid moves: allow them to play their turn
        if (!_CurrGame->makeTurn(next_move, static_cast<Color>(turn_count % 2), in_check)) {
            std::cout << "Invalid move" << std::endl;
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

        turn_count++;
    }
}

void Manager::closeGame() {
    std::cout << "Game over" << std::endl;
    _CurrGame = nullptr;
}

LeaderBoard& Manager::getLeaderBoard() {
    if (_leaderBoard == nullptr) {
        _leaderBoard = std::make_unique<LeaderBoard>();
    }

    return *_leaderBoard;
}