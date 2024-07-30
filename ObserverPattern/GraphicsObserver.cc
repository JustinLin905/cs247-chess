#include "GraphicsObserver.h"

#include "../ChessBoard/ChessBoard.h"

GraphicsObserver::GraphicsObserver(std::weak_ptr<ChessBoard> chess_board) : _chess_board(chess_board) {
    _w = std::make_unique<Xwindow>(900, 900);
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
        _w->drawString(100 * i + 45, 55, std::string{char(64 + i)}, false, false);
    }

    // Render side coordinate column
    for (int i = 1; i < 9; ++i) {
        _w->fillRectangle(0, 100 * i, 100, 100, Xwindow::Green);
        _w->drawString(45, 100 * i + 55, std::to_string(9 - i), false, false);
    }
}

GraphicsObserver::~GraphicsObserver() {}

void GraphicsObserver::notify() {
    render();
}

void GraphicsObserver::render() {
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
            _w->drawString(100 * (j + 1) + 35, 100 * (i + 1) + 55, std::string{color_indicator} + std::string{cur}, false, !isWhite);
        }
    }
}

void GraphicsObserver::peek(Position pos) {
    std::shared_ptr<ChessBoard> board_shared = _chess_board.lock();

    if (!board_shared) {
        throw std::invalid_argument("Invalid chess board while GraphicsObserver is trying to peek");
    }

    auto square = board_shared->getSquare(pos);
    if (square.getPiece() == nullptr) {
        std::cout << "No piece to peek at this position" << std::endl;
        return;
    };

    // If any squares are rendered as peeked before, this, we need to redraw them
    render();

    std::unordered_set<Move> valid_moves = square.getPiece()->getValidMoves();
    for (auto move : valid_moves) {
        prev_state.at(move.final_pos.r).at(move.final_pos.c) = 'X';
        _w->fillRectangle(100 * (move.final_pos.c + 1), 100 * (move.final_pos.r + 1), 100, 100, Xwindow::Blue);

        // if the move is a capture, fill the square with red and draw the piece
        if (board_shared->getSquare(move.final_pos).getPiece() != nullptr) {
            _w->fillRectangle(100 * (move.final_pos.c + 1), 100 * (move.final_pos.r + 1), 100, 100, Xwindow::Red);
            char color_indicator = board_shared->getSquare(move.final_pos).getPiece()->getColor() == Color::WHITE ? 'w' : 'b';
            _w->drawString(100 * (move.final_pos.c + 1) + 35, 100 * (move.final_pos.r + 1) + 55, std::string{color_indicator} + std::string{board_shared->getSquare(move.final_pos).getState()}, false, true);
        }
    }
}