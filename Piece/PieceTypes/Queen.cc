#include "Queen.h"

Queen::Queen(Color color, std::shared_ptr<Player> player,
             std::shared_ptr<ChessBoard> board, std::shared_ptr<Square> square)
    : Piece(color, player, board, square) {}

char Queen::getPieceChar() const { return _color == Color::WHITE ? 'Q' : 'q'; }

// TODO
std::unordered_set<Position> Queen::getAttackedSquares() const {
  return std::unordered_set<Position>();
}