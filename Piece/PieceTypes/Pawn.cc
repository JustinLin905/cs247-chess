#include "Pawn.h"

char Pawn::getPieceChar() const { return _color == Color::WHITE ? 'P' : 'p'; }