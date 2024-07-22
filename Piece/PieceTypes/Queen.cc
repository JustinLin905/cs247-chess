#include "Queen.h"

Queen::Queen(Color color, std::shared_ptr<Player> player)
    : Piece(color, player) {}

char Queen::getPieceChar() const { return _color == Color::WHITE ? 'Q' : 'q'; }