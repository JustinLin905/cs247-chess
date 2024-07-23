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
    if (row - 1 >= 0) {
      if (col - 1 >= 0) {
        attackedSquares.insert(Position{row - 1, col - 1});
      }
      if (col + 1 < 8) {
        attackedSquares.insert(Position{row - 1, col + 1});
      }
    }
  } else {
    if (row + 1 < 8) {
      if (col - 1 >= 0) {
        attackedSquares.insert(Position{row + 1, col - 1});
      }
      if (col + 1 < 8) {
        attackedSquares.insert(Position{row + 1, col + 1});
      }
    }
  }
  return attackedSquares;
}