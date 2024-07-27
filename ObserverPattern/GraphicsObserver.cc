#include "GraphicsObserver.h"

GraphicsObserver::GraphicsObserver(std::shared_ptr<ChessBoard> chess_board)
    : _chess_board(chess_board) {
  _w = new Xwindow(800, 800);
  _chess_board->attach(std::make_unique<GraphicsObserver>(*this));
}

GraphicsObserver::~GraphicsObserver() { delete _w; }

void GraphicsObserver::notify() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if ((i + j) % 2 == 0) {
        _w->fillRectangle(100 * j, 100 * i, 100, 100, Xwindow::White);
      } else {
        _w->fillRectangle(100 * j, 100 * i, 100, 100, Xwindow::Black);
      }

      // If square is occupied by piece, render text
      if (_chess_board->getSquare(Position{i, j}).getPiece() == nullptr) {
        continue;
      }

      char cur =
          _chess_board->getSquare(Position{i, j}).getPiece()->getPieceChar();

      _w->drawString(100 * j + 50, 100 * i + 50, std::string(1, cur));
    }
  }
}