#include "Pawn.h"

Pawn::Pawn(Color color, std::shared_ptr<Player> player)
    : Piece(color, player) {}

char Pawn::getPieceChar() const { return _color == Color::WHITE ? 'P' : 'p'; }