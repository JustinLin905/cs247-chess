#include "Bishop.h"

Bishop::Bishop(Color color, Player* player,
               std::shared_ptr<ChessBoard> board,
               std::shared_ptr<Square> square)
    : Piece(color, player, board, square) {}

char Bishop::getPieceChar() const { return _color == Color::WHITE ? 'B' : 'b'; }

std::unordered_set<Position> Bishop::getAttackedSquares() const {
  std::unordered_set<Position> attacked_squares;
  attackDiagonal(attacked_squares);
  return attacked_squares;
}