#include "Knight.h"

Knight::Knight(Color color, Player* player,
               std::shared_ptr<ChessBoard> board,
               std::shared_ptr<Square> square)
    : Piece(color, player, board, square) {}

char Knight::getPieceChar() const { return _color == Color::WHITE ? 'N' : 'n'; }

std::unordered_set<Position> Knight::getAttackedSquares() const {
  std::unordered_set<Position> attackedSquares;

  if (_square == nullptr) {
    std::cout << "Error: Square is null" << std::endl;
    return attackedSquares;
  }

  Position currentPos = _square->getPosition();
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