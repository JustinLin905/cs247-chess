#include "Pawn.h"

Pawn::Pawn(Color color, Player* player, std::weak_ptr<ChessBoard> board, std::weak_ptr<Square> square)
    : Piece(color, player, board, square) {}

char Pawn::getPieceChar() const { return _color == Color::WHITE ? 'P' : 'p'; }

std::unordered_set<Position> Pawn::getAttackedSquares() const {
    std::unordered_set<Position> attackedSquares;
    Position currentPos = getSquare()->getPosition();
    int row = currentPos.r;
    int col = currentPos.c;

    if (_color == Color::WHITE) {
        tryAttackSquare(Position{row - 1, col - 1}, attackedSquares);
        tryAttackSquare(Position{row - 1, col + 1}, attackedSquares);
    } else {
        tryAttackSquare(Position{row + 1, col - 1}, attackedSquares);
        tryAttackSquare(Position{row + 1, col + 1}, attackedSquares);
    }
    return attackedSquares;
}

/*
Only has move for moving forward by one square.
TODO: NEED UPDATE
*/
std::unordered_set<Move> Pawn::getValidMoves() const {
    Position currentPos = getSquare()->getPosition();
    int row = currentPos.r;
    int col = currentPos.c;
    Position nextPos = _color == Color::WHITE ? Position{row - 1, col} : Position{row + 1, col};

    return std::unordered_set<Move>{Move{currentPos, nextPos, MoveType::UNDETERMINED}};
}