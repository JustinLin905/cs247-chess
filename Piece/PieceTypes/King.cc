#include "King.h"

King::King(Color color, Player* player,
           std::shared_ptr<ChessBoard> board, std::weak_ptr<Square> square)
    : Piece(color, player, board, square) {}

char King::getPieceChar() const { return _color == Color::WHITE ? 'K' : 'k'; }

std::unordered_set<Position> King::getAttackedSquares() const {
    std::unordered_set<Position> attackedSquares;
    Position currentPos = getSquare()->getPosition();
    int row = currentPos.r;
    int col = currentPos.c;

    tryAttackSquare(Position{row - 1, col - 1}, attackedSquares);
    tryAttackSquare(Position{row - 1, col}, attackedSquares);
    tryAttackSquare(Position{row - 1, col + 1}, attackedSquares);
    tryAttackSquare(Position{row, col - 1}, attackedSquares);
    tryAttackSquare(Position{row, col + 1}, attackedSquares);
    tryAttackSquare(Position{row + 1, col - 1}, attackedSquares);
    tryAttackSquare(Position{row + 1, col}, attackedSquares);
    tryAttackSquare(Position{row + 1, col + 1}, attackedSquares);

    return attackedSquares;
}