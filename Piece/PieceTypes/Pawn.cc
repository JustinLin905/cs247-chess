#include "Pawn.h"

Pawn::Pawn(Color color, Player* player, std::weak_ptr<ChessBoard> board, std::weak_ptr<Square> square)
    : Piece(color, player, board, square) {}

char Pawn::getPieceChar() const { return _color == Color::WHITE ? 'P' : 'p'; }

std::unordered_set<Position> Pawn::getAttackedSquares() const {
    std::unordered_set<Position> attackedSquares;
    Position currentPos = getSquare()->getPosition();
    int row = currentPos.r;
    int col = currentPos.c;

    // only attacked squares if there's a piece there
    auto temp_board_ptr = _board.lock();

    if (_color == Color::WHITE) {
        if (temp_board_ptr->getSquare(Position{row - 1, col - 1}).getPiece() != nullptr) attackedSquares.insert(Position{row - 1, col - 1});
        if (temp_board_ptr->getSquare(Position{row - 1, col + 1}).getPiece() != nullptr) attackedSquares.insert(Position{row - 1, col + 1});
    } else {
        if (temp_board_ptr->getSquare(Position{row + 1, col - 1}).getPiece() != nullptr) attackedSquares.insert(Position{row + 1, col - 1});
        if (temp_board_ptr->getSquare(Position{row + 1, col + 1}).getPiece() != nullptr) attackedSquares.insert(Position{row + 1, col + 1});
    }

    Position nextPos = _color == Color::WHITE ? Position{row - 1, col} : Position{row + 1, col};
    if (temp_board_ptr->getSquare(nextPos).getPiece() == nullptr) attackedSquares.insert(nextPos);  // default attack

    if (!_moved) {
        Position nextPos2 = _color == Color::WHITE ? Position{row - 2, col} : Position{row + 2, col};
        attackedSquares.insert(nextPos2);
    }

    return attackedSquares;
}

/*
Only has move for moving forward by one square.
TODO: NEED UPDATE
*/
// std::unordered_set<Move> Pawn::getValidMoves() const {
//     Position currentPos = getSquare()->getPosition();
//     int row = currentPos.r;
//     int col = currentPos.c;
//     Position nextPos = _color == Color::WHITE ? Position{row - 1, col} : Position{row + 1, col};

//     return std::unordered_set<Move>{Move{currentPos, nextPos, MoveType::UNDETERMINED}};
// }