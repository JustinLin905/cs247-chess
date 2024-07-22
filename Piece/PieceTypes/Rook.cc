#include "Rook.h"

Rook::Rook(Color color, std::shared_ptr<Player> player)
    : Piece(color, player) {}

char Rook::getPieceChar() const { return _color == Color::WHITE ? 'R' : 'r'; }