#include "Game.h"

#include <iostream>
#include <memory>

#include "../Move/Move.h"
#include "../Player/HumanPlayer.h"
#include "../PlayerType/PlayerType.h"

void Game::initPlayers(PlayerType::Type white, PlayerType::Type black) {
    if (white == PlayerType::Type::HUMAN) _white = std::unique_ptr<HumanPlayer>(new HumanPlayer(Color::WHITE, *this));
    if (black == PlayerType::Type::HUMAN) _black = std::unique_ptr<HumanPlayer>(new HumanPlayer(Color::BLACK, *this));
}

bool Game::makeTurn(Move move) {
    return true;
}

void Game::reverseMoves(int n) {
}
