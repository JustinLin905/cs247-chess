#include "Square.h"

#include "../Piece/Piece.h"
#include "../Player/Player.h"

Square::Square(Position position) : _position(position) {}

bool Square::isEmpty() const { return _piece.expired(); }

void Square::setPosition(Position position) { _position = position; }

Position Square::getPosition() const { return _position; }

void Square::setPiece(std::shared_ptr<Piece> piece, bool isNew) {
    _piece = piece;
    if (isNew && !_piece.expired()) piece->getPlayer()->addAlivePiece(piece);
}

void Square::disconnectPiece() {
    _piece.reset();
}

std::shared_ptr<Piece> Square::getPiece() const { return _piece.lock(); }

char Square::getState() const {
    auto piece_shared = _piece.lock();
    return piece_shared ? _piece.lock()->getPieceChar() : '-';
}