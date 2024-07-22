#include "Piece.h"

#include "../ChessBoard/Square.h"
#include "../Player/Player.h"

Piece::Piece(Color color, std::shared_ptr<Player> player)
    : _player(player), _color(color) {}
