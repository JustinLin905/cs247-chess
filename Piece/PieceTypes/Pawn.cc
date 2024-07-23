#include "Pawn.h"

Pawn::Pawn(Color color, std::shared_ptr<Player> player,
           std::shared_ptr<ChessBoard> board)
    : Piece(color, player, board) {}

char Pawn::getPieceChar() const { return _color == Color::WHITE ? 'P' : 'p'; }

std::unordered_set<Position> Pawn::getAttackedSquares() const {
  std::unordered_set<Position> attackedSquares;
  Position currentPos = _square->getPosition();
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