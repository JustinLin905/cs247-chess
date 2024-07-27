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
            bool isWhite = (i + j) % 2 == 0;

            // Draw squares
            if (isWhite) {
                _w->fillRectangle(100 * j, 100 * i, 100, 100, Xwindow::White);
            } else {
                _w->fillRectangle(100 * j, 100 * i, 100, 100, Xwindow::Black);
            }

            if (_chess_board->getSquare(Position{i, j}).getPiece() == nullptr) {
                continue;
            }

            // Square is occupied by piece
            char cur =
                _chess_board->getSquare(Position{i, j}).getPiece()->getPieceChar();

            drawPiece(cur, i, j, isWhite);
        }
    }
}

void GraphicsObserver::drawPiece(char piece, int row, int col, bool isWhite) {
    // Draw piece on the window
    // RN IM using the wrong bool for isWhite, I need to getColor on the piece
    std::string piece_str =
        isWhite ? "w" + std::string(1, piece) : "b" + std::string(1, piece);
    _w->drawString(100 * col + 40, 100 * row + 60, piece_str,
                   isWhite ? Xwindow::White : Xwindow::Black);
}