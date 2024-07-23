#include "Queen.h"

Queen::Queen(Color color, std::shared_ptr<Player> player,
             std::shared_ptr<ChessBoard> board)
    : Piece(color, player, board) {}

char Queen::getPieceChar() const { return _color == Color::WHITE ? 'Q' : 'q'; }

// TODO
std::unordered_set<Position> Queen::getAttackedSquares() const {
  return std::unordered_set<Position>();
}