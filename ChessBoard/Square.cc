#include "Square.h"

#include "../Piece/Piece.h"

Square::Square(Position position) : _position(position), _piece{nullptr} {}

bool Square::isEmpty() const { return _piece == nullptr; }

void Square::setPosition(Position position) { _position = position; }

Position Square::getPosition() const { return _position; }

std::unique_ptr<Piece> Square::setPiece(std::unique_ptr<Piece> piece) {
    std::unique_ptr<Piece> old = std::move(_piece);
    _piece = std::move(piece);
    return old;
}

Piece *Square::getPiece() const { return _piece.get(); }

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