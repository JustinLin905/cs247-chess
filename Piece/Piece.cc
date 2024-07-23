#include "Piece.h"

#include "../ChessBoard/ChessBoard.h"
#include "../ChessBoard/Square.h"
#include "../Player/Player.h"

Piece::Piece(Color color, std::shared_ptr<Player> player,
             std::shared_ptr<ChessBoard> board)
    : _player(player), _color(color), _board(board) {}

Color Piece::getColor() const { return _color; }

bool Piece::tryAttackSquare(
    Position pos, std::unordered_set<Position>& attacked_squares) const {
  if (pos.r < 0 || pos.r >= 8 || pos.c < 0 || pos.c >= 8) {
    return false;
  }

  if (_board->getSquare(pos).isEmpty()) {
    attacked_squares.insert(pos);
    return true;
  } else {
    if (_board->getSquare(pos).getPiece()->getColor() != _color) {
      attacked_squares.insert(pos);
    }
    return false;
  }
}
