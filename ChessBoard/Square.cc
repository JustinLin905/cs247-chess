#include "Square.h"

Square::Square(Position position) : _position(position) {}

bool Square::isEmpty() const { return _piece == nullptr; }

void Square::setPiece(std::unique_ptr<Piece> piece) {
  _piece = std::move(piece);
}

char Square::getState() const {
  if (_piece == nullptr) {
    return '-';
  }
  return _piece->getPieceChar();
}

bool Square::isAttacked(Color color) const {
  // needs implementation
  return false;
}