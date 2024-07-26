#include "Player.h"

#include "../Piece/Piece.h"

Player::Player(Color color, Game &game) : _color(color), _game{game} {}

void Player::resign() {
    // needs implementation
}