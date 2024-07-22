#include "King.h"

King::King(Color color, std::shared_ptr<Player> player)
    : Piece(color, player) {}

char King::getPieceChar() const { return _color == Color::WHITE ? 'K' : 'k'; }