#include "Knight.h"

Knight::Knight(Color color, std::shared_ptr<Player> player,
               std::shared_ptr<ChessBoard> board)
    : Piece(color, player, board) {}

char Knight::getPieceChar() const { return _color == Color::WHITE ? 'N' : 'n'; }

// TODO
std::unordered_set<Position> Knight::getAttackedSquares() const {
  return std::unordered_set<Position>();
}