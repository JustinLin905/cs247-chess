#include "Game.h"

#include <iostream>
#include <memory>

#include "../Move/Move.h"
#include "../ObserverPattern/TextObserver.h"
#include "../Player/HumanPlayer.h"
#include "../PlayerType/PlayerType.h"

Game::Game(PlayerType::Type white, PlayerType::Type black) : _chess_board(std::make_shared<ChessBoard>()), text_observer{TextObserver(_chess_board, std::cout)}, graphics_observer{GraphicsObserver(_chess_board)} {
    if (white == PlayerType::Type::HUMAN) _white = std::make_unique<HumanPlayer>(Color::WHITE, shared_from_this());
    if (black == PlayerType::Type::HUMAN) _black = std::make_unique<HumanPlayer>(Color::BLACK, shared_from_this());

    _chess_board = std::make_shared<ChessBoard>();
}

void Game::initDefaultGame() {
    _chess_board->defaultSetup();
}

bool Game::makeTurn(Move move) {
    auto initial = move.initial_pos;
    auto final = move.final_pos;

    Square& init_square = _chess_board->getSquare(initial);
    Square& final_square = _chess_board->getSquare(final);

    auto piece_at_init = init_square.getPiece();
    // auto piece_at_final = final_square.getPiece();

    if (piece_at_init == nullptr) return false;

    final_square.setPiece(init_square.setPiece(nullptr));

    _chess_board->render();  // rerender board

    return true;  // move was valid
}

void Game::renderBoard() const {
    _chess_board->render();
}

void Game::reverseMoves(int n) {
}

Player& Game::getWhite() const {
    return *_white;
}

Player& Game::getBlack() const {
    return *_black;
}
