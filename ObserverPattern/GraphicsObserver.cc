#include "GraphicsObserver.h"

#include "../ChessBoard/ChessBoard.h"

GraphicsObserver::GraphicsObserver(std::weak_ptr<ChessBoard> chess_board) : _chess_board(chess_board) {
    _w = new Xwindow(800, 800);
    _chess_board.lock()->attach(this);
}

GraphicsObserver::~GraphicsObserver() { delete _w; }

void GraphicsObserver::notify() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            bool isWhite = (i + j) % 2 == 0;
            if (isWhite) {
                _w->fillRectangle(100 * j, 100 * i, 100, 100, Xwindow::White);
            } else {
                _w->fillRectangle(100 * j, 100 * i, 100, 100, Xwindow::Black);
            }

            // If square is occupied by piece, render text
            char cur = _chess_board.lock()->getSquare(Position{i, j}).getState();
            if (cur == '-') continue;

            // Draw a small white rectangle as a background if the piece is on a black
            // square
            if (!isWhite) {
                int largeWidth = 100;   // width of the larger rectangle
                int largeHeight = 100;  // height of the larger rectangle
                int x = 100 * j;        // X coordinate of the larger rectangle's top-left corner
                int y = 100 * i;        // Y coordinate of the larger rectangle's top-left corner

                // Calculate the center position of the larger rectangle
                int centerX = x + (largeWidth / 2);
                int centerY = y + (largeHeight / 2);

                // Adjust the coordinates to center the white rectangle
                int whiteRectX = centerX - 10;  // 10 is half of the white rectangle's width (20 / 2)
                int whiteRectY = centerY - 10;  // 10 is half of the white rectangle's height (20 / 2)

                _w->fillRectangle(whiteRectX, whiteRectY, 25, 25, Xwindow::White);
            }

            // Add a "w" or "b" to the piece to indicate color
            char color_indicator = _chess_board.lock()->getSquare(Position{i, j}).getPiece()->getColor() == Color::WHITE ? 'w' : 'b';
            _w->drawString(100 * j + 50, 100 * i + 50, std::string{color_indicator} + std::string{cur});
        }
    }
}