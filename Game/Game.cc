#include "Game.h"

#include <iostream>
#include <memory>

#include "../Player/HumanPlayer.h"
#include "../PlayerType/PlayerType.h"

Game::Game(PlayerType::Type white, PlayerType::Type black) : _chess_board(std::make_shared<ChessBoard>()), _text_observer{std::make_shared<TextObserver>(_chess_board, std::cout)}, _graphics_observer{std::make_shared<GraphicsObserver>(_chess_board)} {
    if (white == PlayerType::Type::HUMAN) _white = std::make_unique<HumanPlayer>(Color::WHITE, std::shared_ptr<Game>(this));
    if (black == PlayerType::Type::HUMAN) _black = std::make_unique<HumanPlayer>(Color::BLACK, std::shared_ptr<Game>(this));
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
    // std::cout << &text_observer << std::endl;
    // std::cout << _chess_board->observers.size() + " HI" << std::endl;
}

void Game::reverseMoves(int n) {
}

Player& Game::getWhite() const {
    return *_white;
}

Player& Game::getBlack() const {
    return *_black;
}
