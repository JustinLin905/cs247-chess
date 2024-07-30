#include "Knight.h"

Knight::Knight(Color color, std::weak_ptr<ChessBoard> board, std::weak_ptr<Square> square) : Piece(color, board, square) {}

char Knight::getPieceChar() const { return _color == Color::WHITE ? 'N' : 'n'; }

std::unordered_set<Position> Knight::getAttackedSquares() const {
    std::unordered_set<Position> attackedSquares;

    Position currentPos = getSquare()->getPosition();
    int row = currentPos.r;
    int col = currentPos.c;

    tryAttackSquare(Position{row - 2, col - 1}, attackedSquares);
    tryAttackSquare(Position{row - 2, col + 1}, attackedSquares);
    tryAttackSquare(Position{row - 1, col - 2}, attackedSquares);
    tryAttackSquare(Position{row - 1, col + 2}, attackedSquares);
    tryAttackSquare(Position{row + 1, col - 2}, attackedSquares);
    tryAttackSquare(Position{row + 1, col + 2}, attackedSquares);
    tryAttackSquare(Position{row + 2, col - 1}, attackedSquares);
    tryAttackSquare(Position{row + 2, col + 1}, attackedSquares);

    return attackedSquares;
}