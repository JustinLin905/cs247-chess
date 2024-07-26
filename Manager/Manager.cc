#include "Manager.h"

#include <iostream>

#include "../CommandInterpreter/CommandInterpreter.h"

Manager::Manager() {}

void Manager::setupGame() {}

void Manager::startGame(PlayerType::Type white, PlayerType::Type black) {
    _CurrGame.initPlayers(white, black);
    int turn_count = 0;

    // Game loop
    while (true) {
        Move next_move = turn_count % 2 == 0 ? _CurrGame.getWhite().getMove() : _CurrGame.getBlack().getMove();

        if (!_CurrGame.makeTurn(next_move)) {
            std::cout << "Invalid move" << std::endl;
            continue;
        }

        turn_count++;
    }
}

void Manager::closeGame() {}