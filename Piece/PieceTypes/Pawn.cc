#include "Pawn.h"

Pawn::Pawn(Color color, Player* player,
           std::shared_ptr<ChessBoard> board, std::shared_ptr<Square> square)
    : Piece(color, player, board, square) {}

char Pawn::getPieceChar() const { return _color == Color::WHITE ? 'P' : 'p'; }

std::unordered_set<Position> Pawn::getAttackedSquares() const {
  std::unordered_set<Position> attackedSquares;
  if (_square == nullptr) {
    std::cout << "Error: Square is null" << std::endl;
    return attackedSquares;
  }
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