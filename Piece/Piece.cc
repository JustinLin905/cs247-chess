#include "Piece.h"

#include "../ChessBoard/ChessBoard.h"
#include "../ChessBoard/Square.h"
#include "../Manager/Manager.h"
#include "../Player/Player.h"

Piece::Piece(Color color, Player* player, std::weak_ptr<ChessBoard> board, std::weak_ptr<Square> square) : _color(color), _player(player), _board(board), _square(square) {}

Color Piece::getColor() const { return _color; }
Player* Piece::getPlayer() const { return _player; }

/*
tryAttackSquare is a helper function that checks if a square can be attacked by
this piece. Handles bounds checking and opposing color checking.

Returns true if the loop using this function should continue searching in this
direction, false otherwise.
*/
bool Piece::tryAttackSquare(
    Position pos, std::unordered_set<Position>& attacked_squares) const {
    if (pos.r < 0 || pos.r >= 8 || pos.c < 0 || pos.c >= 8) {
        return false;
    }

    std::shared_ptr<ChessBoard> board_shared = _board.lock();
    if (!board_shared) {
        std::cerr << "Error: Board is null" << std::endl;
        return false;
    }

    if (board_shared->getSquare(pos).isEmpty()) {
        attacked_squares.insert(pos);
        return true;
    } else {
        if (board_shared->getSquare(pos).getPiece()->getColor() != _color) {
            attacked_squares.insert(pos);
        }
        return false;
    }
}

std::shared_ptr<Square> Piece::getSquare() const {
    auto square_shared = _square.lock();
    if (!square_shared) {
        std::cerr << "Error: Square is null" << std::endl;
        throw std::runtime_error("Square is null");
    }

    return square_shared;
}

/*
Methods to handle attacking diagonally.

Re-used by Bishop and Queen.
*/
void Piece::attackDiagonal(
    std::unordered_set<Position>& attacked_squares) const {
    Position current_pos = getSquare()->getPosition();

    // Check all diagonals
    for (int i = 1; i < 8; i++) {
        Position next_pos = Position{current_pos.r + i, current_pos.c + i};
        if (!tryAttackSquare(next_pos, attacked_squares)) {
            break;
        }
    }

    for (int i = 1; i < 8; i++) {
        Position next_pos = Position{current_pos.r - i, current_pos.c - i};
        if (!tryAttackSquare(next_pos, attacked_squares)) {
            break;
        }
    }

    for (int i = 1; i < 8; i++) {
        Position next_pos = Position{current_pos.r + i, current_pos.c - i};
        if (!tryAttackSquare(next_pos, attacked_squares)) {
            break;
        }
    }

    for (int i = 1; i < 8; i++) {
        Position next_pos = Position{current_pos.r - i, current_pos.c + i};
        if (!tryAttackSquare(next_pos, attacked_squares)) {
            break;
        }
    }
}

/*
Methods to handle attacking straight.

Re-used by Rook and Queen.
*/
void Piece::attackStraight(
    std::unordered_set<Position>& attacked_squares) const {
    Position current_pos = getSquare()->getPosition();
    int row = current_pos.r;
    int col = current_pos.c;

    // Check all squares to the right of the piece
    for (int i = col + 1; i < 8; i++) {
        if (!tryAttackSquare(Position{row, i}, attacked_squares)) {
            break;
        }
    }

    // Check all squares to the left of the piece
    for (int i = col - 1; i >= 0; i--) {
        if (!tryAttackSquare(Position{row, i}, attacked_squares)) {
            break;
        }
    }

    // Check all squares above the piece
    for (int i = row - 1; i >= 0; i--) {
        if (!tryAttackSquare(Position{i, col}, attacked_squares)) {
            break;
        }
    }

    // Check all squares below the piece
    for (int i = row + 1; i < 8; i++) {
        if (!tryAttackSquare(Position{i, col}, attacked_squares)) {
            break;
        }
    }
}

/*
Get all valid moves of a piece.
By default, the valid moves of a piece is the same as the squares they attack.
This method will be overridden for special cases (ex. Pawns)
*/
std::unordered_set<Move> Piece::getValidMoves() const {
    std::unordered_set<Move> validMoves;
    std::unordered_set<Position> attackedSquares = getAttackedSquares();
    Position current_pos = getSquare()->getPosition();

    for (Position p : attackedSquares) {
        if (!Manager::getCurrGame()->simulateLegality(Move{current_pos, p, MoveType::DEFAULT}, _color)) continue;
        validMoves.insert(Move{current_pos, p, MoveType::DEFAULT});
    }

    return validMoves;
}

void Piece::setSquare(std::weak_ptr<Square> square) { _square = square; }
