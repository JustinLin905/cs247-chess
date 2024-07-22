#include "Bishop.h"

Bishop::Bishop(Color color, std::shared_ptr<Player> player)
    : Piece(color, player) {}

char Bishop::getPieceChar() const { return _color == Color::WHITE ? 'B' : 'b'; }