#include "Game.h"

#include <iostream>

#include "../Move/Move.h"
#include "../Player/HumanPlayer.h"
#include "../PlayerType/PlayerType.h"

void Game::initPlayers(PlayerType::Type white, PlayerType::Type black) {
    if (white == PlayerType::Type::HUMAN) _white = HumanPlayer(Color::WHITE);
    if (black == PlayerType::Type::HUMAN) _black = HumanPlayer(Color::BLACK);
}

bool Game::makeTurn(Move move) {
    return true;
}

void Game::reverseMoves(int n) {
}
