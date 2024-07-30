#include "GraphicsObserver.h"

#include "../ChessBoard/ChessBoard.h"

GraphicsObserver::GraphicsObserver(std::weak_ptr<ChessBoard> chess_board) : _chess_board(chess_board) {
    _w = new Xwindow(900, 900);
    std::shared_ptr<ChessBoard> board_shared = chess_board.lock();

    if (!board_shared) {
        throw std::invalid_argument("Invalid chess board while GraphicsObserver is trying to attach");
    }

    board_shared->attach(this);
    for (int i = 0; i < 8; ++i) {
        std::vector<char> row;
        for (int j = 0; j < 8; ++j) {
            // Set to an invalid character to force a redraw on all squares
            row.push_back('/');
        }

        prev_state.push_back(row);
    }

    // Render top coordinate row
    for (int i = 1; i < 9; ++i) {
        _w->fillRectangle(100 * i, 0, 100, 100, Xwindow::Green);
        _w->drawString(100 * i + 45, 55, std::string{char(64 + i)}, false);
    }

    // Render side coordinate column
    for (int i = 1; i < 9; ++i) {
        _w->fillRectangle(0, 100 * i, 100, 100, Xwindow::Green);
        _w->drawString(45, 100 * i + 55, std::to_string(9 - i), false);
    }
}

GraphicsObserver::~GraphicsObserver() {
    delete _w;
}

void GraphicsObserver::notify() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            // Only redraw the square if it has changed
            char cur = _chess_board.lock()->getSquare(Position{i, j}).getState();
            if (cur == prev_state.at(i).at(j)) continue;

            prev_state.at(i).at(j) = cur;

            bool isWhite = (i + j) % 2 == 0;
            if (isWhite) {
                _w->fillRectangle(100 * (j + 1), 100 * (i + 1), 100, 100, Xwindow::White);
            } else {
                _w->fillRectangle(100 * (j + 1), 100 * (i + 1), 100, 100, Xwindow::Black);
            }

            // Skip piece drawing if the square is empty
            if (cur == '-') continue;

            // Add a "w" or "b" to the piece to indicate color
            char color_indicator = _chess_board.lock()->getSquare(Position{i, j}).getPiece()->getColor() == Color::WHITE ? 'w' : 'b';
            _w->drawString(100 * (j + 1) + 35, 100 * (i + 1) + 55, std::string{color_indicator} + std::string{cur}, !isWhite);
        }
    }
}