#include "Rook.h"

#include "../../ChessBoard/ChessBoard.h"

Rook::Rook(Color color, std::shared_ptr<Player> player,
           std::shared_ptr<ChessBoard> board, std::shared_ptr<Square> square)
    : Piece(color, player, board, square) {}

char Rook::getPieceChar() const { return _color == Color::WHITE ? 'R' : 'r'; }

std::unordered_set<Position> Rook::getAttackedSquares() const {
  std::unordered_set<Position> attackedSquares;
  attackStraight(attackedSquares);
  return attackedSquares;
}