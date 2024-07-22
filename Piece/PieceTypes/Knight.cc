#include "Knight.h"

Knight::Knight(Color color, std::shared_ptr<Player> player)
    : Piece(color, player) {}

char Knight::getPieceChar() const { return _color == Color::WHITE ? 'N' : 'n'; }