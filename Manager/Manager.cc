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

    _CurrGame->getBlack().removeDeadPiece(_CurrGame->_chess_board->getSquare(Position{0, 0}).getPiece());

    int turn_count = 0;

    // Game loop
    while (true) {
        Move next_move = turn_count % 2 == 0 ? _CurrGame->getWhite().getMove() : _CurrGame->getBlack().getMove();

        if (!_CurrGame->makeTurn(next_move, static_cast<Color>(turn_count % 2))) {
            std::cout << "Invalid move" << std::endl;
            continue;
        }

        // for debugging
        for (auto i : _CurrGame->getBlack()._alive_pieces) {
            std::cout << i->getPieceChar() << " ";
        }

        std::cout << std::endl;

        for (auto i : _CurrGame->getWhite()._alive_pieces) {
            std::cout << i->getPieceChar() << " ";
        }

        std::cout << std::endl;

        turn_count++;
    }
}

void Manager::closeGame() { std::cout << "Game over" << std::endl; }

LeaderBoard& Manager::getLeaderBoard() {
    if (_leaderBoard == nullptr) {
        _leaderBoard = std::make_unique<LeaderBoard>();
    }

    return *_leaderBoard;
}