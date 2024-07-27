#include "Manager.h"

#include <iostream>

#include "../CommandInterpreter/CommandInterpreter.h"
#include "../Game/Game.h"
#include "../PlayerType/PlayerType.h"

std::shared_ptr<Game> Manager::_CurrGame = nullptr;

Manager::Manager() {}

void Manager::setupGame() {}

void Manager::startGame(PlayerType::Type white, PlayerType::Type black) {
    _CurrGame = std::make_shared<Game>(white, black);
    _CurrGame->initDefaultGame();

    _CurrGame->renderBoard();

    int turn_count = 0;

    // Game loop
    while (true) {
        Move next_move = turn_count % 2 == 0 ? _CurrGame->getWhite().getMove() : _CurrGame->getBlack().getMove();

        if (!_CurrGame->makeTurn(next_move)) {
            std::cout << "Invalid move" << std::endl;
            continue;
        }

        turn_count++;
    }
}

void Manager::closeGame() {
    std::cout << "Game over" << std::endl;
}