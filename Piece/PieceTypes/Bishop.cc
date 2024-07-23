#include "Bishop.h"

Bishop::Bishop(Color color, std::shared_ptr<Player> player,
               std::shared_ptr<ChessBoard> board)
    : (Color color, std::shared_ptr<Player> player,
       std::shared_ptr<ChessBoard> board, std::unique_ptr<Square> square) {}

char Bishop::getPieceChar() const { return _color == Color::WHITE ? 'B' : 'b'; }

std::unordered_set<Position> Bishop::getAttackedSquares() const {
  std::unordered_set<Position> attacked_squares;
  Position currentPos = _square->getPosition();

  // Check all diagonals
  for (int i = 1; i < 8; i++) {
    Position next_pos = Position{currentPos.r + i, currentPos.c + i};
    if (!tryAttackSquare(next_pos, attacked_squares)) {
      break;
    }
  }

  for (int i = 1; i < 8; i++) {
    Position next_pos = Position{currentPos.r - i, currentPos.c - i};
    if (!tryAttackSquare(next_pos, attacked_squares)) {
      break;
    }
  }

  for (int i = 1; i < 8; i++) {
    Position next_pos = Position{currentPos.r + i, currentPos.c - i};
    if (!tryAttackSquare(next_pos, attacked_squares)) {
      break;
    }
  }

  for (int i = 1; i < 8; i++) {
    Position next_pos = Position{currentPos.r - i, currentPos.c + i};
    if (!tryAttackSquare(next_pos, attacked_squares)) {
      break;
    }
  }

  return attacked_squares;
}